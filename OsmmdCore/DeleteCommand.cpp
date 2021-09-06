/*
* Created by Zeng Yinuo, 2021.09.06
*/

#include "DeleteCommand.h"

Osmmd::DeleteCommand::DeleteCommand(const DeleteCommandArg& arg)
    : m_arg(arg)
{
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::DeleteCommand::DoExecute()
{
    return std::shared_ptr<CommandResult>();
}
