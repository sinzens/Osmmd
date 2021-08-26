/*
* Created by Zeng Yinuo, 2021.08.23
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    class CommandLineParser
    {
    public:
        CommandLineParser(const CommandLineParser& other) = delete;
        CommandLineParser& operator=(const CommandLineParser& other) = delete;

        std::vector<std::string> ParseArguments(int argc, char* argv[]);

        static CommandLineParser& GetInstance();

    private:
        CommandLineParser();
    };
}
