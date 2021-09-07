/*
* Created by Zeng Yinuo, 2021.09.07
*/

#include "DeleteDatabaseCommand.h"

Osmmd::DeleteDatabaseCommand::DeleteDatabaseCommand(const DeleteDatabaseCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::DeleteDatabase;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::DeleteDatabaseCommand::DoExecute()
{
    return std::make_shared<CommandResult>();
}
