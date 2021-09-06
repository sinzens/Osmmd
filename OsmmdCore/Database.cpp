/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.06
*/

#include "Database.h"

Osmmd::Database::Database(const DatabaseConfiguration& config)
    : m_config(config)
{
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
