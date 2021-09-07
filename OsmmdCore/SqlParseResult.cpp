/*
* Created by Zeng Yinuo, 2021.09.07
*/

#include "SqlParseResult.h"
#include "Enum.h"

Osmmd::SqlParseResult::SqlParseResult()
    : Successful(true)
    , Command(nullptr)
{
}

Osmmd::SqlParseResult::SqlParseResult(const SqlParseResult& other)
    : Successful(other.Successful)
    , Message(other.Message)
    , Command(other.Command)
{
}

Osmmd::SqlParseResult::SqlParseResult(bool successful, const std::string& message)
    : Successful(successful)
    , Message(message)
    , Command(nullptr)
{
}

Osmmd::SqlParseResult::SqlParseResult(bool successful, std::shared_ptr<AtomicCommand> command)
    : Successful(successful)
    , Command(command)
{
}

Osmmd::SqlParseResult& Osmmd::SqlParseResult::operator=(const SqlParseResult& other)
{
    this->Successful = other.Successful;
    this->Message = other.Message;
    this->Command = other.Command;

    return *this;
}

std::string Osmmd::SqlParseResult::ToString() const
{
    if (!this->Successful)
    {
        char buffer[200]{};
        sprintf_s(buffer, "SQL Syntax error, message is:\n%s", this->Message.c_str());

        return buffer;
    }

    if (!this->Message.empty())
    {
        char buffer[200]{};
        sprintf_s
        (
            buffer,
            "SQL successfully parsed, command is %s, message is:\n%s",
            GetCommandTypeName(this->Command->GetType()).c_str(),
            this->Message.c_str()
        );

        return buffer;
    }
    
    char buffer[200]{};
    sprintf_s
    (
        buffer,
        "SQL successfully parsed, command is %s",
        GetCommandTypeName(this->Command->GetType()).c_str()
    );

    return buffer;
}

Bytes Osmmd::SqlParseResult::ToBytes() const
{
    return Bytes();
}
