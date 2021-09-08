/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "Driver.h"
#include "StringConstants.h"
#include "SqlParser.h"
#include "Memory.h"

Osmmd::Driver::Driver()
    : m_executor(std::make_unique<CommandExecutor>())
{
}

void Osmmd::Driver::WriteConfiguration() const
{
    std::ofstream writer;
    writer.open(this->GetConfigurationPath(), std::ios::out | std::ios::binary);

    WriteAllBytesToFile(writer, m_config.ToBytes());
}

void Osmmd::Driver::ReadConfiguration()
{
    std::ifstream reader(this->GetConfigurationPath(), std::ios::in | std::ios::binary);

    if (reader.is_open())
    {
        m_config = DriverConfiguration::FromBytes(ReadAllBytesFromFile(reader));
    }
}

void Osmmd::Driver::SetWorkingDirectory(const std::string& directory)
{
    m_workingDirectory = directory;
}

std::string Osmmd::Driver::SetCurrentDatabase(const std::string& name)
{
    if (m_currentDatabase == name)
    {
        return std::string();
    }

    m_currentDatabase = name;

    auto target = m_config.DATABASES.find(name);

    if (target == m_config.DATABASES.end())
    {
        return StringConstants::Error.COMMAND_NO_SUCH_DATABASE;
    }

    if (m_databases.find(name) == m_databases.end())
    {
        std::shared_ptr<Database> database = ReadDatabaseFromFile(target->second);

        if (!database)
        {
            return StringConstants::Error.COMMAND_NO_SUCH_DATABASE;
        }

        m_databases.insert({ name, database });
    }

    return std::string();
}

void Osmmd::Driver::RefreshConfiguration()
{
    this->WriteConfiguration();
}

void Osmmd::Driver::RefreshConfiguration(const DriverConfiguration& config)
{
    m_config = config;
    this->WriteConfiguration();
}

bool Osmmd::Driver::InitEnvironment()
{
    return this->InitConfiguration();
}

bool Osmmd::Driver::InitConfiguration()
{
    std::ifstream reader;

    std::string fileName = this->GetConfigurationPath();

    reader.open(fileName, std::ios::in | std::ios::binary);

    if (reader.is_open())
    {
        m_config = DriverConfiguration::FromBytes(ReadAllBytesFromFile(reader));
        return true;
    }
    else
    {
        std::ofstream writer;
        writer.open(fileName, std::ios::out | std::ios::binary);

        DriverConfiguration config;
        config.NAME = StringConstants::Driver.DRIVER_NAME;

        m_config = config;

        WriteAllBytesToFile(writer, config.ToBytes());

        return false;
    }
}

std::string Osmmd::Driver::GetWorkingDirectory() const
{
    return m_workingDirectory;
}

std::string Osmmd::Driver::GetConfigurationPath() const
{
    return std::filesystem::path(m_workingDirectory).append(StringConstants::Driver.CONFIG_FILE_NAME).u8string();
}

const Osmmd::DriverConfiguration& Osmmd::Driver::GetConfiguration() const
{
    return m_config;
}

const Osmmd::PerformanceConfiguration& Osmmd::Driver::GetPerformance() const
{
    return m_performance;
}

std::shared_ptr<Osmmd::Database> Osmmd::Driver::GetDatabase(const std::string& name) const
{
    auto target = m_databases.find(name);

    if (target == m_databases.end())
    {
        return nullptr;
    }

    return target->second;
}

std::shared_ptr<Osmmd::Database> Osmmd::Driver::GetCurrentDatabase() const
{
    auto target = m_databases.find(m_currentDatabase);

    if (target == m_databases.end())
    {
        return nullptr;
    }

    return target->second;
}

std::string Osmmd::Driver::CreateDatabase(const std::string& name)
{
    if (m_config.DATABASES.find(name) != m_config.DATABASES.end())
    {
        return StringConstants::Error.COMMAND_DATABASE_EXISTS;
    }

    std::filesystem::path path = std::filesystem::path(m_workingDirectory).append(name);

    if (!std::filesystem::exists(path))
    {
        std::filesystem::create_directory(path);
    }

    std::filesystem::path filePath = std::filesystem::path(path).append(name + ".db");

    DatabaseConfiguration config;
    config.NAME = name;
    
    std::ofstream writer(filePath, std::ios::out, std::ios::binary);

    if (writer.is_open())
    {
        WriteAllBytesToFile(writer, config.ToBytes());
    }

    std::shared_ptr<Database> database = std::make_shared<Database>(config);

    m_config.DATABASES.insert({ name, std::filesystem::absolute(filePath).u8string() });
    m_databases.insert({ name, database });

    this->RefreshConfiguration();

    return std::string();
}

std::string Osmmd::Driver::DeleteDatabase(const std::string& name)
{
    auto target = m_config.DATABASES.find(name);

    if (target == m_config.DATABASES.end())
    {
        return StringConstants::Error.COMMAND_NO_SUCH_DATABASE;
    }

    std::filesystem::path databaseDir = std::filesystem::path(target->second).parent_path();
    std::filesystem::remove_all(databaseDir);

    m_config.DATABASES.erase(target);
    m_databases.erase(name);

    m_currentDatabase = std::string();

    this->RefreshConfiguration();

    return std::string();
}

std::vector<std::shared_ptr<Osmmd::CommandResult>> Osmmd::Driver::ExecuteSqls(const std::vector<std::string>& sqls)
{
    for (const std::string& sql : sqls)
    {
        if (sql.empty())
        {
            continue;
        }

        SqlParseResult result = SqlParser::Parse(sql);

        if (!result.Successful)
        {
            m_executor->ClearCommands();
            return { std::make_shared<CommandResult>(CommandType::Select, 0, 0, false, result.ToString(), 0) };
        }

        m_executor->AddCommand(result.Command);
    }

    return m_executor->Execute();
}

Osmmd::Driver& Osmmd::Driver::GetInstance()
{
    static Driver driver;
    return driver;
}

std::shared_ptr<Osmmd::Database> Osmmd::Driver::ReadDatabaseFromFile(const std::string& path)
{
    std::ifstream reader(path, std::ios::in | std::ios::binary);

    if (!reader.is_open())
    {
        return nullptr;
    }
    
    return std::make_shared<Database>(DatabaseConfiguration::FromBytes(ReadAllBytesFromFile(reader)));
}
