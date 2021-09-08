/*
* Created by Zeng Yinuo, 2021.09.08
*/

#include "UseDatabaseCommand.h"
#include "StringConstants.h"
#include "Driver.h"

Osmmd::UseDatabaseCommand::UseDatabaseCommand(const UseDatabaseCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::UseDatabase;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::UseDatabaseCommand::DoExecute()
{
    std::string error = Driver::GetInstance().SetCurrentDatabase(m_arg.Name);

    if (!error.empty())
    {
        return std::make_shared<CommandResult>(CommandType::UseDatabase, 0, 0, false, error, 0);
    }

    return std::make_shared<CommandResult>(CommandType::UseDatabase, 0, 0, true, std::string(), 0);
}
