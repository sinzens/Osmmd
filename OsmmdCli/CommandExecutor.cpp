/*
* Created by Zeng Yinuo, 2021.08.23
*/

#include "CommandExecutor.h"

Osmmd::CommandExecutor::CommandExecutor()
{
}

Osmmd::CommandExecutor& Osmmd::CommandExecutor::GetInstance()
{
    static CommandExecutor executor;
    return executor;
}
