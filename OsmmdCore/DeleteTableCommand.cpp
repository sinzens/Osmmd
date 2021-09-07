/*
* Created by Zeng Yinuo, 2021.09.07
*/

#include "DeleteTableCommand.h"

Osmmd::DeleteTableCommand::DeleteTableCommand(const DeleteTableCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::DeleteTable;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::DeleteTableCommand::DoExecute()
{
    return std::make_shared<CommandResult>();
}
