/*
* Created by Zeng Yinuo, 2021.08.23
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    class CommandExecutor
    {
    public:
        CommandExecutor(const CommandExecutor& other) = delete;
        CommandExecutor& operator=(const CommandExecutor& other) = delete;

        static CommandExecutor& GetInstance();

    private:
        CommandExecutor();
    };
}



