/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
*/

#include "Database.h"

Osmmd::Database::Database(const DatabaseConfiguration& config)
    : m_config(config)
{
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

    std::filebuf* buffer = reader.rdbuf();

    long long size = buffer->pubseekoff(0, std::ios::end, std::ios::in);
    buffer->pubseekpos(0, std::ios::in);

    char* data = new char[size];
    buffer->sgetn(data, size);

    reader.close();

    std::shared_ptr<DataTable> table = DataTable::PtrFromBytes(Bytes(data, data + size));

    delete[] data;

    return table;
}
