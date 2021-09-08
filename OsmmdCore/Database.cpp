/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "Database.h"
#include "StringConstants.h"
#include "Driver.h"
#include "Memory.h"

Osmmd::Database::Database(const DatabaseConfiguration& config)
    : m_config(config)
{
}

Osmmd::Database::~Database()
{
    for (auto i = m_tables.begin(); i != m_tables.end(); i++)
    {
        std::string path = m_config.TABLES.at(i->first);
        WriteTableToFile(path, i->second);
    }
}

const Osmmd::DatabaseConfiguration& Osmmd::Database::GetConfiguration() const
{
    return m_config;
}

std::shared_ptr<Osmmd::DataTable> Osmmd::Database::GetTable(const std::string& name)
{
    auto path = m_config.TABLES.find(name);

    if (path == m_config.TABLES.end())
    {
        return nullptr;
    }

    auto target = m_tables.find(name);

    if (target != m_tables.end())
    {
        return target->second;
    }

    std::shared_ptr<DataTable> table = ReadTableFromFile(path->second);
    m_tables.insert({ name, table });

    return table;
}

std::string Osmmd::Database::CreateTable(const DataTableConfiguration& config, const Row& rowDefinition)
{
    if (m_config.TABLES.find(config.NAME) != m_config.TABLES.end())
    {
        return StringConstants::Error.COMMAND_TABLE_EXISTS;
    }

    char buffer[50]{};
    sprintf_s(buffer, "osmmd_%s.table", config.NAME.c_str());

    std::filesystem::path path = std::filesystem::path(this->GetWorkingDirectory()).append(std::string(buffer));

    std::shared_ptr<DataTable> table = std::make_shared<DataTable>(config, rowDefinition);

    std::ofstream writer(path, std::ios::out | std::ios::binary);
    
    if (writer.is_open())
    {
        WriteAllBytesToFile(writer, table->ToBytes());
    }

    m_config.TABLES.insert({ config.NAME, std::filesystem::absolute(path).u8string() });
    m_tables.insert({ config.NAME, table });

    this->RefreshConfiguration();

    return std::string();
}

std::string Osmmd::Database::DeleteTable(const std::string& name)
{
    auto target = m_config.TABLES.find(name);

    if (target == m_config.TABLES.end())
    {
        return StringConstants::Error.COMMAND_NO_SUCH_TABLE;
    }

    std::filesystem::remove(target->second);

    m_config.TABLES.erase(target);
    m_tables.erase(name);

    this->RefreshConfiguration();

    return std::string();
}

void Osmmd::Database::RefreshConfiguration()
{
    std::ofstream writer(this->GetConfigFilePath(), std::ios::out | std::ios::binary);

    if (writer.is_open())
    {
        WriteAllBytesToFile(writer, m_config.ToBytes());
    }
}

void Osmmd::Database::RefreshConfiguration(const DatabaseConfiguration& config)
{
    m_config = config;
    this->RefreshConfiguration();
}

std::string Osmmd::Database::ToString() const
{
    return m_config.ToString();
}

Bytes Osmmd::Database::ToBytes() const
{
    return m_config.ToBytes();
}

Osmmd::Database Osmmd::Database::FromBytes(const Bytes& bytes)
{
    return Database(DatabaseConfiguration::FromBytes(bytes));
}

std::shared_ptr<Osmmd::Database> Osmmd::Database::PtrFromBytes(const Bytes& bytes)
{
    return std::make_shared<Database>(DatabaseConfiguration::FromBytes(bytes));
}

std::shared_ptr<Osmmd::DataTable> Osmmd::Database::ReadTableFromFile(const std::string& path)
{
    std::ifstream reader(path, std::ios::in | std::ios::binary);

    if (!reader.is_open())
    {
        return nullptr;
    }

    return DataTable::PtrFromBytes(ReadAllBytesFromFile(reader));
}

void Osmmd::Database::WriteTableToFile(const std::string& path, std::shared_ptr<DataTable> table)
{
    std::ofstream writer(path, std::ios::out | std::ios::binary);

    if (writer.is_open())
    {
        WriteAllBytesToFile(writer, table->ToBytes());
    }
}

std::string Osmmd::Database::GetConfigFilePath() const
{
    return Driver::GetInstance().GetConfiguration().DATABASES.at(m_config.NAME);
}

std::string Osmmd::Database::GetWorkingDirectory() const
{
    return std::filesystem::path(this->GetConfigFilePath()).parent_path().u8string();
}
