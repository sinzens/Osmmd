/*
* Created by Zeng Yinuo, 2021.08.23
*/

#include "CommandParser.h"

Osmmd::CommandParser::CommandParser()
{
}

Osmmd::CommandParser& Osmmd::CommandParser::GetInstance()
{
    static CommandParser parser;
    return parser;
}
