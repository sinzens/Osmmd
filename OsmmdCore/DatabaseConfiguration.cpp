/*
* Created by Zeng Yinuo, 2021.09.05
*/

#include "DatabaseConfiguration.h"

std::string Osmmd::DatabaseConfiguration::ToString() const
{
    return std::string();
}

Bytes Osmmd::DatabaseConfiguration::ToBytes() const
{
    return Bytes();
}

Osmmd::DatabaseConfiguration Osmmd::DatabaseConfiguration::FromBytes(const Bytes& bytes)
{
    return DatabaseConfiguration();
}

Osmmd::DatabaseConfiguration& Osmmd::DatabaseConfiguration::operator=(const DatabaseConfiguration& other)
{
    this->NAME = other.NAME;
    this->TABLES = other.TABLES;
    
    return *this;
}
