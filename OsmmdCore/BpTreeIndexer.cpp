/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "BpTreeIndexer.h"

std::shared_ptr<Osmmd::IndexResult> Osmmd::BpTreeIndexer::Insert
(
    std::shared_ptr<ColumnValue> key,
    std::shared_ptr<RowValue> value
)
{
    return std::make_shared<IndexResult>();
}

std::shared_ptr<Osmmd::SelectIndexResult> Osmmd::BpTreeIndexer::Delete(const std::vector<Condition>& conditions)
{
    return std::make_shared<SelectIndexResult>();
}

std::shared_ptr<Osmmd::SelectIndexResult> Osmmd::BpTreeIndexer::Update
(
    const std::vector<Condition>& conditions,
    const Row& updateRow,
    const Row& originalRow,
    std::shared_ptr<RowValue> updateValue
)
{
    return std::make_shared<SelectIndexResult>();
}

std::shared_ptr<Osmmd::IndexResult> Osmmd::BpTreeIndexer::UpdateKeyword
(
    std::shared_ptr<ColumnValue> newKey,
    std::shared_ptr<ColumnValue> oldKey
)
{
    return std::make_shared<IndexResult>();
}

std::shared_ptr<Osmmd::SelectIndexResult> Osmmd::BpTreeIndexer::Select
(
    const std::vector<Condition>& conditions,
    const Row& selectRow,
    const Row& originalRow
) const
{
    return std::make_shared<SelectIndexResult>();
}

std::shared_ptr<Osmmd::RowValue> Osmmd::BpTreeIndexer::DirectSelect(std::shared_ptr<ColumnValue> key) const
{
    return std::make_shared<RowValue>();
}

std::string Osmmd::BpTreeIndexer::ToString() const
{
    return std::string();
}

Bytes Osmmd::BpTreeIndexer::ToBytes() const
{
    return Bytes();
}

Osmmd::BpTreeIndexer Osmmd::BpTreeIndexer::FromBytes(int keyIndex, const Row& rowDefinition, const Bytes& bytes)
{
    return BpTreeIndexer();
}

std::shared_ptr<Osmmd::BpTreeIndexer> Osmmd::BpTreeIndexer::PtrFromBytes(int keyIndex, const Row& rowDefinition, const Bytes& bytes)
{
    return std::make_shared<BpTreeIndexer>(BpTreeIndexer::FromBytes(keyIndex, rowDefinition, bytes));
}
