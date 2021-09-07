/*
* Created by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "AtomicCommand.h"

namespace Osmmd
{
    struct OSMMD_CORE_API SqlParseResult : public ISerializable
    {
        bool Successful;
        std::string Message;
        std::shared_ptr<AtomicCommand> Command;

        SqlParseResult();
        SqlParseResult(const SqlParseResult& other);
        SqlParseResult(bool successful, const std::string& message);
        SqlParseResult(bool successful, std::shared_ptr<AtomicCommand> command);

        SqlParseResult& operator=(const SqlParseResult& other);

        std::string ToString() const override;
        Bytes ToBytes() const override;

    };
}
