/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
*/

#include "BpTreeIndexer.h"

std::shared_ptr<Osmmd::IndexResult> Osmmd::BpTreeIndexer::Insert
(
    std::shared_ptr<ColumnValue> key,
    std::shared_ptr<RowValue> value
)
{
    return std::shared_ptr<IndexResult>();
}

std::shared_ptr<Osmmd::SelectIndexResult> Osmmd::BpTreeIndexer::Delete(const std::vector<Condition>& conditions)
{
    return std::shared_ptr<SelectIndexResult>();
}

std::shared_ptr<Osmmd::IndexResult> Osmmd::BpTreeIndexer::Update
(
    const std::vector<Condition>& conditions,
    const Row& updateRow,
    const Row& originalRow,
    std::shared_ptr<RowValue> updateValue
)
{
    return std::shared_ptr<IndexResult>();
}

std::shared_ptr<Osmmd::IndexResult> Osmmd::BpTreeIndexer::UpdateKeyword
(
    std::shared_ptr<ColumnValue> newKey,
    std::shared_ptr<ColumnValue> oldKey
)
{
    return std::shared_ptr<IndexResult>();
}

std::shared_ptr<Osmmd::SelectIndexResult> Osmmd::BpTreeIndexer::Select
(
    const std::vector<Condition>& conditions,
    const Row& selectRow,
    const Row& originalRow
) const
{
    return std::shared_ptr<SelectIndexResult>();
}

std::shared_ptr<Osmmd::RowValue> Osmmd::BpTreeIndexer::DirectSelect(std::shared_ptr<ColumnValue> key) const
{
    return std::shared_ptr<RowValue>();
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
