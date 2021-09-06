/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "RowValue.h"
#include "CommandResult.h"
#include "SelectCommandResult.h"

namespace Osmmd
{
    class OSMMD_CORE_API Indexer : public ISerializable
    {
    public:
        virtual std::shared_ptr<CommandResult> Insert(const ColumnValue& key, std::shared_ptr<RowValue> value) = 0;

        virtual std::shared_ptr<CommandResult> Delete(const ColumnValue& key) = 0;

        virtual std::shared_ptr<CommandResult> Update(const ColumnValue& key, std::shared_ptr<RowValue> value) = 0;

        virtual std::shared_ptr<SelectCommandResult> Select(const ColumnValue& key) const = 0;
        virtual std::shared_ptr<SelectCommandResult> Select(std::function<bool(std::shared_ptr<RowValue>)> filter) const = 0;
    };
}
