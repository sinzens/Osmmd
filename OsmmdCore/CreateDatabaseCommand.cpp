/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
*/

#include "CreateDatabaseCommand.h"
#include "Driver.h"

Osmmd::CreateDatabaseCommand::CreateDatabaseCommand(const CreateDatabaseCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::CreateDatabase;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::CreateDatabaseCommand::DoExecute()
{
    Driver& driver = Driver::GetInstance();
    DriverConfiguration config = driver.GetConfiguration();

    std::filesystem::path path(driver.GetWorkingDirectory());
    path.append(m_arg.Name).append(std::string(m_arg.Name).append(".database"));

    config.DATABASES.insert({ m_arg.Name, path.u8string() });

    driver.RefreshConfiguration(config);

    return std::make_shared<CommandResult>();
}
