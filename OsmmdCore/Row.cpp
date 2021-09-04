/*
* Created by Zeng Yinuo, 2021.09.01
* Edited by Zeng Yinuo, 2021.09.04
*/

#include "Row.h"

std::string Osmmd::Row::ToString() const
{
    std::string result;

    char headerBuffer[50]{};
    sprintf_s(headerBuffer, "Row: (Column size: %lld)\n", this->Columns.size());

    result.append(headerBuffer);

    for (int i = 0; i < this->Columns.size(); i++)
    {
        char buffer[150]{};
        sprintf_s(buffer, "\tColumn %d: %s\n", i + 1, this->Columns.at(i).ToString().c_str());

        result.append(buffer);
    }

    return std::string();
}

Bytes Osmmd::Row::ToBytes() const
{
    return Bytes();
}
