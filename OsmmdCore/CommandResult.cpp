/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
* Edited by Zeng Yinuo, 2021.09.09
*/

#include "CommandResult.h"
#include "Driver.h"
#include "Enum.h"

Osmmd::CommandResult::CommandResult()
    : Type(CommandType::Select)
    , AffectRowCount(0)
    , AffectColCount(0)
    , Successful(true)
    , Message(std::string())
    , TimeElapse(0)
{
}

Osmmd::CommandResult::CommandResult(const CommandResult& other)
    : Type(other.Type)
    , AffectRowCount(other.AffectRowCount)
    , AffectColCount(other.AffectColCount)
    , Successful(other.Successful)
    , Message(other.Message)
    , TimeElapse(other.TimeElapse)
{
}

Osmmd::CommandResult::CommandResult
(
    CommandType type,
    int row,
    int col,
    bool successful,
    const std::string& message,
    double time
)
    : Type(type)
    , AffectRowCount(row)
    , AffectColCount(col)
    , Successful(successful)
    , Message(message)
    , TimeElapse(time)
{
}

std::string Osmmd::CommandResult::ToString() const
{
    char buffer[1000]{};
    std::string result;

    if (!this->Successful)
    {
        sprintf_s(buffer, "Execution failed;\nError message is:\n%s;", this->Message.c_str());
        result = buffer;
    }
    else
    {
        if (this->Message.empty())
        {
            sprintf_s
            (
                buffer,
                "Execution succeeded;\nCommand type: %s;\n%d rows affected;\n%d cols affected;",
                GetCommandTypeName(this->Type).c_str(),
                this->AffectRowCount,
                this->AffectColCount
            );
        }
        else
        {
            sprintf_s
            (
                buffer,
                "Execution succeeded;\nCommand type: %s;\n%d rows affected;\n%d cols affected;\nMessage is:\n%s;",
                GetCommandTypeName(this->Type).c_str(),
                this->AffectRowCount,
                this->AffectColCount,
                this->Message.c_str()
            );
        }

        result = buffer;

        if (Driver::GetInstance().GetPerformance().TIMING)
        {
            char timeBuffer[50]{};
            sprintf_s(timeBuffer, "\nTime cost: %gms", this->TimeElapse);

            result.append(timeBuffer);
        }
    }

    return result;
}

Bytes Osmmd::CommandResult::ToBytes() const
{
    return Bytes();
}

Osmmd::CommandResult& Osmmd::CommandResult::operator=(const CommandResult& other)
{
    this->Type = other.Type;
    this->AffectRowCount = other.AffectRowCount;
    this->AffectColCount = other.AffectColCount;
    this->Successful = other.Successful;
    this->Message = other.Message;
    this->TimeElapse = other.TimeElapse;

    return *this;
}
