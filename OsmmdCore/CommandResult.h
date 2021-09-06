/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "ISerializable.h"
#include "CommandType.h"

namespace Osmmd
{
    struct OSMMD_CORE_API CommandResult : public ISerializable
    {
        CommandType Type;

        int AffectRowCount;
        int AffectColCount;

        bool Successful;

        std::string Message;

        double TimeElapse;

        CommandResult();
        CommandResult(const CommandResult& other);
        CommandResult
        (
            CommandType type,
            int row,
            int col,
            bool successful,
            const std::string& message,
            double time
        );

        std::string ToString() const override;
        Bytes ToBytes() const override;

        CommandResult& operator=(const CommandResult& other);
    };
}
