/*
* Created by Zeng Yinuo, 2021.09.06
*/

#include "SelectCommand.h"
#include "SelectCommandResult.h"

Osmmd::SelectCommand::SelectCommand(const SelectCommandArg& arg)
    : m_arg(arg)
{
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::SelectCommand::DoExecute()
{
    return std::shared_ptr<CommandResult>();
}
