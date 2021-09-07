/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
*/

#include "Driver.h"
#include "StringConstants.h"
#include "SqlParser.h"

Osmmd::Driver::Driver()
    : m_executor(std::make_unique<CommandExecutor>())
{
}

void Osmmd::Driver::WriteConfiguration() const
{
    std::ofstream writer;
    writer.open(this->GetConfigurationPath(), std::ios::out | std::ios::binary);

    Bytes data = m_config.ToBytes();

    writer << std::string(data.begin(), data.end()) << std::endl;
    writer.close();
}

void Osmmd::Driver::ReadConfiguration()
{
    std::ifstream reader(this->GetConfigurationPath(), std::ios::in | std::ios::binary);

    if (reader.is_open())
    {
        std::string buffer = std::string(std::istreambuf_iterator<char>(reader), std::istreambuf_iterator<char>());
        m_config = DriverConfiguration::FromBytes(Bytes(buffer.begin(), buffer.end()));

        reader.close();
    }
}

void Osmmd::Driver::SetWorkingDirectory(const std::string& directory)
{
    m_workingDirectory = directory;
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
        std::string buffer = std::string(std::istreambuf_iterator<char>(reader), std::istreambuf_iterator<char>());
        m_config = DriverConfiguration::FromBytes(Bytes(buffer.begin(), buffer.end()));
        reader.close();

        return true;
    }
    else
    {
        std::ofstream writer;
        writer.open(fileName, std::ios::out | std::ios::binary);

        DriverConfiguration configTest;

        configTest.NAME = StringConstants::Driver.DRIVER_NAME;
        configTest.DATABASES.insert({ "test_db", "Test" });
        configTest.DATABASES.insert({ "test_db2", "Test2" });

        Bytes data = configTest.ToBytes();

        writer << std::string(data.begin(), data.end()) << std::endl;
        writer.close();

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
    return std::shared_ptr<Database>();
}

void Osmmd::Driver::ExecuteSqls(const std::vector<std::string>& sqls)
{
    for (const std::string& sql : sqls)
    {
        SqlParseResult result = SqlParser::Parse(sql);

        if (!result.Successful)
        {
            std::cout << result.ToString() << std::endl;
            return;
        }

        m_executor->AddCommand(result.Command);
    }

    m_executor->Execute();
}

Osmmd::Driver& Osmmd::Driver::GetInstance()
{
    static Driver driver;
    return driver;
}
