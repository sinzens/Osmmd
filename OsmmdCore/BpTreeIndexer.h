/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "Indexer.h"
#include "Row.h"

namespace Osmmd
{
    class OSMMD_CORE_API BpTreeIndexer : public Indexer
    {
    public:
        std::shared_ptr<CommandResult> Insert(const ColumnValue& key, std::shared_ptr<RowValue> value) override;

        std::shared_ptr<CommandResult> Delete(const ColumnValue& key) override;

        std::shared_ptr<CommandResult> Update(const ColumnValue& key, std::shared_ptr<RowValue> value) override;

        std::shared_ptr<SelectCommandResult> Select(const ColumnValue& key) const override;
        std::shared_ptr<SelectCommandResult> Select(std::function<bool(std::shared_ptr<RowValue>)> filter) const override;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static BpTreeIndexer FromBytes(const Row& rowDefinition, const Bytes& bytes);
        static std::shared_ptr<BpTreeIndexer> PtrFromBytes(const Row& rowDefinition, const Bytes& bytes);
    };
}
