/*
* Created by Zeng Yinuo, 2021.08.26
*/

#include "Database.h"

Osmmd::Database::Database(const std::string& name)
    : m_name(name)
{
}

const std::string& Osmmd::Database::GetName() const
{
    return m_name;
}
