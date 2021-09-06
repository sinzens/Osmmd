/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
*/

#include "HashIndexer.h"

std::shared_ptr<Osmmd::IndexResult> Osmmd::HashIndexer::Insert
(
    std::shared_ptr<ColumnValue> key,
    std::shared_ptr<RowValue> value
)
{
    m_hashMap.insert({ ColumnValueToBytesForHash(key), value });

    return std::make_shared<IndexResult>(1, value->Values.size());
}

std::shared_ptr<Osmmd::SelectIndexResult> Osmmd::HashIndexer::Delete(const std::vector<Condition>& conditions)
{
    std::shared_ptr<SelectIndexResult> result = std::make_shared<SelectIndexResult>();

    for (auto i = m_hashMap.begin(); i != m_hashMap.end(); i++)
    {
        if (i->second->MeetConditions(conditions))
        {
            result->Results->emplace_back(std::make_shared<RowValue>(i->second));
            i = m_hashMap.erase(i);
        }
    }

    result->AffectRowCount = result->Results->size();
    result->AffectColCount = result->Results->size() == 0 ? 0 : result->Results->front()->Values.size();

    return result;
}

std::shared_ptr<Osmmd::IndexResult> Osmmd::HashIndexer::Update
(
    const std::vector<Condition>& conditions,
    const Row& updateRow,
    const Row& originalRow,
    std::shared_ptr<RowValue> updateValue
)
{
    int counter = 0;

    for (auto i = m_hashMap.begin(); i != m_hashMap.end(); i++)
    {
        if (i->second->MeetConditions(conditions))
        {
            i->second->Update(updateRow, originalRow, updateValue);
            counter++;
        }
    }

    return std::make_shared<IndexResult>(counter, updateRow.Columns.size());
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
    return Bytes();
}

Osmmd::HashIndexer Osmmd::HashIndexer::FromBytes(const Row& rowDefinition, const Bytes& bytes)
{
    return HashIndexer();
}

std::shared_ptr<Osmmd::HashIndexer> Osmmd::HashIndexer::PtrFromBytes(const Row& rowDefinition, const Bytes& bytes)
{
    return std::shared_ptr<HashIndexer>();
}

std::string Osmmd::HashIndexer::ColumnValueToBytesForHash(std::shared_ptr<ColumnValue> value)
{
    return std::string(value->Data.GetBytes().begin(), value->Data.GetBytes().end());
}
