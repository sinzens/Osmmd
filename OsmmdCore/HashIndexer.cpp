/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "HashIndexer.h"

std::shared_ptr<Osmmd::IndexResult> Osmmd::HashIndexer::Insert
(
    std::shared_ptr<ColumnValue> key,
    std::shared_ptr<RowValue> value
)
{
    std::string keyData = ColumnValueToBytesForHash(key);

    if (m_hashMap.find(keyData) != m_hashMap.end())
    {
        return DuplicateKeyResult(key->ToString());
    }

    m_hashMap.insert({ keyData, value });

    return std::make_shared<IndexResult>(1, value->Values.size());
}

std::shared_ptr<Osmmd::SelectIndexResult> Osmmd::HashIndexer::Delete(const std::vector<Condition>& conditions)
{
    std::shared_ptr<SelectIndexResult> result = std::make_shared<SelectIndexResult>();

    for (auto i = m_hashMap.begin(); i != m_hashMap.end();)
    {
        if (i->second->MeetConditions(conditions))
        {
            result->Results->emplace_back(std::make_shared<RowValue>(i->second));
            m_hashMap.erase(i++);
        }
        else
        {
            i++;
        }
    }

    result->AffectRowCount = result->Results->size();
    result->AffectColCount = result->Results->size() == 0 ? 0 : result->Results->front()->Values.size();

    return result;
}

std::shared_ptr<Osmmd::SelectIndexResult> Osmmd::HashIndexer::Update
(
    const std::vector<Condition>& conditions,
    const Row& updateRow,
    const Row& originalRow,
    std::shared_ptr<RowValue> updateValue
)
{
    int counter = 0;

    std::shared_ptr<std::vector<std::shared_ptr<RowValue>>> oldValues
        = std::make_shared<std::vector<std::shared_ptr<RowValue>>>();

    for (auto i = m_hashMap.begin(); i != m_hashMap.end(); i++)
    {
        if (i->second->MeetConditions(conditions))
        {
            std::shared_ptr<RowValue> oldValue = std::make_shared<RowValue>(i->second->DeepCopy());
            oldValues->emplace_back(oldValue);

            i->second->Update(updateRow, originalRow, updateValue);
            counter++;
        }
    }

    return std::make_shared<SelectIndexResult>(counter, updateRow.Columns.size(), oldValues);
}

std::shared_ptr<Osmmd::IndexResult> Osmmd::HashIndexer::UpdateKeyword
(
    std::shared_ptr<ColumnValue> newKey,
    std::shared_ptr<ColumnValue> oldKey
)
{
    std::shared_ptr<IndexResult> result = std::make_shared<IndexResult>();

    auto target = m_hashMap.find(ColumnValueToBytesForHash(oldKey));

    if (target == m_hashMap.end())
    {
        return result;
    }

    std::shared_ptr<RowValue> value = target->second;

    m_hashMap.erase(target);
    m_hashMap.insert({ ColumnValueToBytesForHash(newKey), value });

    result->AffectRowCount = 1;
    result->AffectColCount = 1;

    return result;
}

std::shared_ptr<Osmmd::SelectIndexResult> Osmmd::HashIndexer::Select
(
    const std::vector<Condition>& conditions,
    const Row& selectRow,
    const Row& originalRow
) const
{
    std::shared_ptr<SelectIndexResult> result = std::make_shared<SelectIndexResult>();

    for (auto i = m_hashMap.begin(); i != m_hashMap.end(); i++)
    {
        if (i->second->MeetConditions(conditions))
        {
            result->Results->emplace_back(std::make_shared<RowValue>(i->second->Sliced(selectRow, originalRow)));
        }
    }

    return result;
}

std::shared_ptr<Osmmd::RowValue> Osmmd::HashIndexer::DirectSelect(std::shared_ptr<ColumnValue> key) const
{
    auto target = m_hashMap.find(ColumnValueToBytesForHash(key));

    if (target == m_hashMap.end())
    {
        return nullptr;
    }

    return target->second;
}

std::string Osmmd::HashIndexer::ToString() const
{
    std::string result;

    for (auto i = m_hashMap.begin(); i != m_hashMap.end(); i++)
    {
        char buffer[255]{};
        sprintf_s(buffer, "\t%s: %s", i->first.c_str(), i->second->ToString().c_str());

        result.append(buffer).append("\n");
    }

    return result;
}

Bytes Osmmd::HashIndexer::ToBytes() const
{
    Bytes bytes;
    Bytes dataCountData = Value::FromInteger(static_cast<int32_t>(m_hashMap.size())).GetBytes();

    bytes.insert(bytes.end(), dataCountData.begin(), dataCountData.end());

    for (auto i = m_hashMap.begin(); i != m_hashMap.end(); i++)
    {
        Bytes rowBytes = i->second->ToBytes();
        bytes.insert(bytes.end(), rowBytes.begin(), rowBytes.end());
    }

    Bytes dataLengthData = Value::FromInteger(static_cast<int32_t>(bytes.size()) + sizeof(int32_t)).GetBytes();

    bytes.insert(bytes.begin(), dataLengthData.begin(), dataLengthData.end());

    return bytes;
}

Osmmd::HashIndexer Osmmd::HashIndexer::FromBytes(int keyIndex, const Row& rowDefinition, const Bytes& bytes)
{
    HashIndexer indexer;

    auto dataCountBegin = bytes.begin() + sizeof(int32_t);
    auto rowDataBlockBegin = dataCountBegin + sizeof(int32_t);

    int dataCount = Value::GetLengthFromBytesHead(Bytes(dataCountBegin, rowDataBlockBegin));

    int rowDataLength = rowDefinition.GetLength();
    int rowDataBeginIndex = rowDataBlockBegin - bytes.begin();

    for (int i = 0; i < dataCount; i++)
    {
        auto rowDataBegin = bytes.begin() + rowDataBeginIndex;
        auto rowDataEnd = rowDataBegin + rowDataLength;

        std::shared_ptr<RowValue> value
            = std::make_shared<RowValue>(RowValue::FromBytes(rowDefinition, Bytes(rowDataBegin, rowDataEnd)));

        std::shared_ptr<ColumnValue> key = value->Values.at(keyIndex);
        indexer.m_hashMap.insert({ ColumnValueToBytesForHash(key), value });

        rowDataBeginIndex = rowDataEnd - bytes.begin();
    }

    return indexer;
}

std::shared_ptr<Osmmd::HashIndexer> Osmmd::HashIndexer::PtrFromBytes(int keyIndex, const Row& rowDefinition, const Bytes& bytes)
{
    return std::make_shared<HashIndexer>(HashIndexer::FromBytes(keyIndex, rowDefinition, bytes));
}

std::string Osmmd::HashIndexer::ColumnValueToBytesForHash(std::shared_ptr<ColumnValue> value)
{
    return std::string(value->Data.GetBytes().begin(), value->Data.GetBytes().end());
}
