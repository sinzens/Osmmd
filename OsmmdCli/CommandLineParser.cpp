/*
* Created by Zeng Yinuo, 2021.08.23
*/

#include "CommandLineParser.h"

Osmmd::CommandLineParser::CommandLineParser()
{
}

std::vector<std::string> Osmmd::CommandLineParser::ParseArguments(int argc, char* argv[])
{
    std::vector<std::string> args;

    for (int i = 0; i < argc; i++)
    {
        args.emplace_back(argv[i]);
    }

    return args;
}

Osmmd::CommandLineParser& Osmmd::CommandLineParser::GetInstance()
{
    static CommandLineParser parser;
    return parser;
}
