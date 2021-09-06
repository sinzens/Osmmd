/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
*/

#include "BpTreeIndexer.h"

std::shared_ptr<Osmmd::CommandResult> Osmmd::BpTreeIndexer::Insert(const ColumnValue& key, std::shared_ptr<RowValue> value)
{
    return nullptr;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::BpTreeIndexer::Delete(const ColumnValue& key)
{
    return nullptr;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::BpTreeIndexer::Update(const ColumnValue& key, std::shared_ptr<RowValue> value)
{
    return nullptr;
}

std::shared_ptr<Osmmd::SelectCommandResult> Osmmd::BpTreeIndexer::Select(const ColumnValue& key) const
{
    return nullptr;
}

std::shared_ptr<Osmmd::SelectCommandResult> Osmmd::BpTreeIndexer::Select(std::function<bool(std::shared_ptr<RowValue>)> filter) const
{
    return nullptr;
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
