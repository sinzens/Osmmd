/*
* Created by Zeng Yinuo, 2021.09.06
*/

#include "InsertCommand.h"

Osmmd::InsertCommand::InsertCommand(const InsertCommandArg& arg)
    : m_arg(arg)
{
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::InsertCommand::DoExecute()
{
    return std::shared_ptr<CommandResult>();
}
