/*
* Created by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "DeleteTableCommand.h"
#include "StringConstants.h"
#include "Driver.h"

Osmmd::DeleteTableCommand::DeleteTableCommand(const DeleteTableCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::DeleteTable;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::DeleteTableCommand::DoExecute()
{
    std::shared_ptr<Database> database = Driver::GetInstance().GetCurrentDatabase();

    if (!database)
    {
        return this->NoCurrentDatabaseResult();
    }

    std::string error = database->DeleteTable(m_arg.Name);

    if (!error.empty())
    {
        return std::make_shared<CommandResult>(CommandType::DeleteTable, 0, 0, false, error, 0);
    }

    return std::make_shared<CommandResult>(CommandType::DeleteTable, 1, 0, true, std::string(), 0);
}
