/*
* Created by Zeng Yinuo, 2021.08.23
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    class CommandParser
    {
    public:
        CommandParser(const CommandParser& other) = delete;
        CommandParser& operator=(const CommandParser& other) = delete;

        static CommandParser& GetInstance();

    private:
        CommandParser();
    };
}
