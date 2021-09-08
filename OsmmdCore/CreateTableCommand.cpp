/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "CreateTableCommand.h"
#include "StringConstants.h"
#include "Driver.h"

Osmmd::CreateTableCommand::CreateTableCommand(const CreateTableCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::CreateTable;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::CreateTableCommand::DoExecute()
{
    std::shared_ptr<Database> database = Driver::GetInstance().GetCurrentDatabase();

    if (!database)
    {
        return this->NoCurrentDatabaseResult();
    }

    std::string error = database->CreateTable(m_arg.Config, m_arg.RowDefinition);

    if (!error.empty())
    {
        return std::make_shared<CommandResult>(CommandType::CreateTable, 0, 0, false, error, 0);
    }

    return std::make_shared<CommandResult>(CommandType::CreateTable, 1, 0, true, std::string(), 0);
}
