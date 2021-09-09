/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.09
*/

#pragma once

#include "CommandResult.h"
#include "RowValue.h"

namespace Osmmd
{
    struct OSMMD_CORE_API SelectCommandResult : public CommandResult
    {
        using CommandResult::CommandResult;

        Row RowDefinition;

        std::shared_ptr<std::vector<std::shared_ptr<RowValue>>> Results;

        SelectCommandResult(const SelectCommandResult& other);

        SelectCommandResult
        (
            CommandType type,
            int row,
            int col,
            bool successful,
            const std::string& message,
            double time,
            const Row& rowDefinition,
            std::shared_ptr<std::vector<std::shared_ptr<RowValue>>> results
        );

        std::string ToString() const override;

        SelectCommandResult& operator=(const SelectCommandResult& other);
    };
}
