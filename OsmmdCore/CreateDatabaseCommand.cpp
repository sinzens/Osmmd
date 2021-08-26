/*
* Created by Zeng Yinuo, 2021.08.26
*/

#include "CreateDatabaseCommand.h"
#include "Driver.h"

Osmmd::CreateDatabaseCommand::CreateDatabaseCommand(const Database& database)
    : m_database(database)
{
}

Osmmd::CommandResult Osmmd::CreateDatabaseCommand::Execute()
{
    Driver& driver = Driver::GetInstance();
    DriverConfiguration config = driver.GetConfiguration();

    std::filesystem::path path(driver.GetWorkingDirectory());
    path.append(m_database.GetName()).append(std::string(m_database.GetName()).append(".database"));

    //config.databases.emplace_back(std::tuple(m_database.GetName(), path.u8string()));
    config.DATABASES.insert({ m_database.GetName(), path.u8string() });

    driver.RefreshConfiguration(config);

    return CommandResult();
}
