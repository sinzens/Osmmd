/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "CreateDatabaseCommand.h"
#include "StringConstants.h"
#include "Driver.h"

Osmmd::CreateDatabaseCommand::CreateDatabaseCommand(const CreateDatabaseCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::CreateDatabase;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::CreateDatabaseCommand::DoExecute()
{
    std::string error = Driver::GetInstance().CreateDatabase(m_arg.Name);

    if (!error.empty())
    {
        return std::make_shared<CommandResult>(CommandType::CreateDatabase, 0, 0, false, error, 0);
    }

    return std::make_shared<CommandResult>(CommandType::CreateDatabase, 1, 0, true, std::string(), 0);
}
