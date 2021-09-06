/*
* Created by Zeng Yinuo, 2021.09.06
*/

#include "UpdateCommand.h"

Osmmd::UpdateCommand::UpdateCommand(const UpdateCommandArg& arg)
    : m_arg(arg)
{
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::UpdateCommand::DoExecute()
{
    return std::shared_ptr<CommandResult>();
}
