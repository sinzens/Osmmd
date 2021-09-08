/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "Indexer.h"
#include "Row.h"

namespace Osmmd
{
    class OSMMD_CORE_API BpTreeIndexer : public Indexer
    {
    public:
        std::shared_ptr<IndexResult> Insert
        (
            std::shared_ptr<ColumnValue> key,
            std::shared_ptr<RowValue> value
        ) override;

        std::shared_ptr<SelectIndexResult> Delete(const std::vector<Condition>& conditions) override;

        std::shared_ptr<SelectIndexResult> Update
        (
            const std::vector<Condition>& conditions,
            const Row& updateRow,
            const Row& originalRow,
            std::shared_ptr<RowValue> updateValue
        ) override;

        std::shared_ptr<IndexResult> UpdateKeyword
        (
            std::shared_ptr<ColumnValue> newKey,
            std::shared_ptr<ColumnValue> oldKey
        ) override;

        std::shared_ptr<SelectIndexResult> Select
        (
            const std::vector<Condition>& conditions,
            const Row& selectRow,
            const Row& originalRow
        ) const override;

        std::shared_ptr<RowValue> DirectSelect(std::shared_ptr<ColumnValue> key) const override;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static BpTreeIndexer FromBytes(int keyIndex, const Row& rowDefinition, const Bytes& bytes);
        static std::shared_ptr<BpTreeIndexer> PtrFromBytes(int keyIndex, const Row& rowDefinition, const Bytes& bytes);
    };
}
