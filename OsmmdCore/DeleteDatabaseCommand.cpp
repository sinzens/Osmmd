/*
* Created by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "DeleteDatabaseCommand.h"
#include "StringConstants.h"
#include "Driver.h"

Osmmd::DeleteDatabaseCommand::DeleteDatabaseCommand(const DeleteDatabaseCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::DeleteDatabase;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::DeleteDatabaseCommand::DoExecute()
{
    std::string error = Driver::GetInstance().DeleteDatabase(m_arg.Name);

    if (!error.empty())
    {
        return std::make_shared<CommandResult>(CommandType::DeleteDatabase, 0, 0, false, error, 0);
    }

    return std::make_shared<CommandResult>(CommandType::DeleteDatabase, 1, 0, true, std::string(), 0);
}
