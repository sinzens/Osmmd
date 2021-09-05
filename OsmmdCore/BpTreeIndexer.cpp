/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#include "BpTreeIndexer.h"

void Osmmd::BpTreeIndexer::Insert(const ColumnValue& key, std::shared_ptr<RowValue> value)
{
}

void Osmmd::BpTreeIndexer::Delete(const ColumnValue& key)
{
}

void Osmmd::BpTreeIndexer::Update(const ColumnValue& key, std::shared_ptr<RowValue> value)
{
}

std::vector<Osmmd::RowValue> Osmmd::BpTreeIndexer::Select(const ColumnValue& key) const
{
    return std::vector<RowValue>();
}

std::vector<Osmmd::RowValue> Osmmd::BpTreeIndexer::Select(std::function<bool(std::shared_ptr<RowValue>)> filter) const
{
    return std::vector<RowValue>();
}

std::string Osmmd::BpTreeIndexer::ToString() const
{
    return std::string();
}

Bytes Osmmd::BpTreeIndexer::ToBytes() const
{
    return Bytes();
}

Osmmd::BpTreeIndexer Osmmd::BpTreeIndexer::FromBytes(const Row& rowDefinition, const Bytes& bytes)
{
    return BpTreeIndexer();
}

std::shared_ptr<Osmmd::BpTreeIndexer> Osmmd::BpTreeIndexer::PtrFromBytes(const Row& rowDefinition, const Bytes& bytes)
{
    return std::shared_ptr<BpTreeIndexer>();
}
