/*
* Created by Zeng Yinuo, 2021.08.26
*/

#include "Driver.h"
#include "DriverConfiguration.h"

static constexpr const char* CONFIG_FILE_NAME = "osmmd.config";
static constexpr const char* DRIVER_NAME = "Osmmd Driver";

Osmmd::Driver::Driver()
{
}

void Osmmd::Driver::WriteConfiguration() const
{
    std::ofstream writer;
    writer.open(this->GetConfigurationPath(), std::ios::out | std::ios::binary);

    writer << m_config.ToBytes() << std::endl;
    writer.close();
}

void Osmmd::Driver::ReadConfiguration()
{
    std::ifstream reader(this->GetConfigurationPath(), std::ios::in | std::ios::binary);

    if (reader.is_open())
    {
        std::string buffer = std::string(std::istreambuf_iterator<char>(reader), std::istreambuf_iterator<char>());
        m_config = DriverConfiguration::FromBytes(buffer);

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
        m_config = DriverConfiguration::FromBytes(buffer);
        reader.close();

        return true;
    }
    else
    {
        std::ofstream writer;
        writer.open(fileName, std::ios::out | std::ios::binary);

        DriverConfiguration configTest;
        /*configTest.driver = "Osmmd Driver";
        configTest.databases.emplace_back(std::tuple<std::string, std::string>("test_db", "Test"));
        configTest.databases.emplace_back(std::tuple<std::string, std::string>("test_db2", "Test2"));*/

        configTest.NAME = DRIVER_NAME;
        configTest.DATABASES.insert({ "test_db", "Test" });
        configTest.DATABASES.insert({ "test_db2", "Test2" });

        writer << configTest.ToBytes() << std::endl;
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
    return std::filesystem::path(m_workingDirectory).append(CONFIG_FILE_NAME).u8string();
}

const Osmmd::DriverConfiguration& Osmmd::Driver::GetConfiguration() const
{
    return m_config;
}

Osmmd::Driver& Osmmd::Driver::GetInstance()
{
    static Driver driver;
    return driver;
}
