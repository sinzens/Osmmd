/*
* Created by Zeng Yinuo, 2021.09.08
*/

#include "UseDatabaseCommand.h"

Osmmd::UseDatabaseCommand::UseDatabaseCommand(const UseDatabaseCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::UseDatabase;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::UseDatabaseCommand::DoExecute()
{
    return std::make_shared<CommandResult>();
}
