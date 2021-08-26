/*
* Created by Zeng Yinuo, 2021.08.26
*/

#include "CommandResult.h"

std::string Osmmd::CommandResult::ToBytes() const
{
    char buffer[1000]{};

    if (!this->successful)
    {
        sprintf_s(buffer, "Execution failed;\nError message is:\n%s;\n", this->message.c_str());
    }
    else
    {
        sprintf_s
        (
            buffer,
            "Execution succeeded;\n%d rows affected;\n%d cols affected;\nMessage is:\n%s;\n",
            this->affectRowCount,
            this->affectColCount,
            this->message.c_str()
        );
    }

    std::string str = buffer;

    return str;
}
