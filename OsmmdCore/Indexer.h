/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "RowValue.h"
#include "IndexResult.h"
#include "SelectIndexResult.h"

namespace Osmmd
{
    class OSMMD_CORE_API Indexer : public ISerializable
    {
    public:
        virtual std::shared_ptr<IndexResult> Insert
        (
            std::shared_ptr<ColumnValue> key,
            std::shared_ptr<RowValue> value
        ) = 0;

        virtual std::shared_ptr<SelectIndexResult> Delete(const std::vector<Condition>& conditions) = 0;

        virtual std::shared_ptr<SelectIndexResult> Update
        (
            const std::vector<Condition>& conditions,
            const Row& updateRow,
            const Row& originalRow,
            std::shared_ptr<RowValue> updateValue
        ) = 0;

        virtual std::shared_ptr<IndexResult> UpdateKeyword
        (
            std::shared_ptr<ColumnValue> newKey,
            std::shared_ptr<ColumnValue> oldKey
        ) = 0;

        virtual std::shared_ptr<SelectIndexResult> Select
        (
            const std::vector<Condition>& conditions,
            const Row& selectRow,
            const Row& originalRow
        ) const = 0;

        virtual std::shared_ptr<RowValue> DirectSelect(std::shared_ptr<ColumnValue> key) const = 0;

    protected:
        static std::shared_ptr<IndexResult> DuplicateKeyResult(const std::string& value);
    };
}
