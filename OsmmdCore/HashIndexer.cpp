/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
*/

#include "HashIndexer.h"

std::shared_ptr<Osmmd::CommandResult> Osmmd::HashIndexer::Insert(const ColumnValue& key, std::shared_ptr<RowValue> value)
{
    m_hashMap.insert({ ColumnValueToBytesForHash(key), value });

    return nullptr;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::HashIndexer::Delete(const ColumnValue& key)
{
    m_hashMap.erase(ColumnValueToBytesForHash(key));

    return nullptr;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::HashIndexer::Update(const ColumnValue& key, std::shared_ptr<RowValue> value)
{
    auto target = m_hashMap.find(ColumnValueToBytesForHash(key));
    
    if (target != m_hashMap.end())
    {
        target->second = value;
    }

    return nullptr;
}

std::shared_ptr<Osmmd::SelectCommandResult> Osmmd::HashIndexer::Select(const ColumnValue& key) const
{
    auto target = m_hashMap.find(ColumnValueToBytesForHash(key));

    if (target != m_hashMap.end())
    {
        //return { *(target->second) };
    }

    return nullptr;
}

std::shared_ptr<Osmmd::SelectCommandResult> Osmmd::HashIndexer::Select(std::function<bool(std::shared_ptr<RowValue>)> filter) const
{
    std::vector<RowValue> results;

    for (auto i = m_hashMap.begin(); i != m_hashMap.end(); i++)
    {
        if (filter(i->second))
        {
            results.emplace_back(*(i->second));
        }
    }

    return nullptr;
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

std::string Osmmd::HashIndexer::ColumnValueToBytesForHash(const ColumnValue& value)
{
    return std::string(value.Data.GetBytes().begin(), value.Data.GetBytes().end());
}
