/*
* Created by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "DatabaseConfiguration.h"
#include "StringConstants.h"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>

static rapidjson::Value JsonString(const std::string& str, rapidjson::MemoryPoolAllocator<>& allocator)
{
    rapidjson::Value value;
    value.SetString(str.c_str(), str.length(), allocator);
    return value;
}

std::string Osmmd::DatabaseConfiguration::ToString() const
{
    Bytes bytes = this->ToBytes();
    return std::string(bytes.begin(), bytes.end());
}

Bytes Osmmd::DatabaseConfiguration::ToBytes() const
{
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    document.AddMember(StringConstants::DatabaseConfiguration.NAME, JsonString(this->NAME, allocator), allocator);

    rapidjson::Value tables(rapidjson::kArrayType);

    for (auto& table : this->TABLES)
    {
        std::string tableName = table.first;
        std::string tablePath = table.second;

        rapidjson::Value tableObject(rapidjson::kObjectType);
        tableObject.AddMember(StringConstants::DatabaseConfiguration.NAME, JsonString(tableName, allocator), allocator);
        tableObject.AddMember(StringConstants::DatabaseConfiguration.PATH, JsonString(tablePath, allocator), allocator);

        tables.PushBack(tableObject, allocator);
    }

    document.AddMember(StringConstants::DatabaseConfiguration.TABLES, tables, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    const char* result = buffer.GetString();
    return Bytes(result, result + buffer.GetSize());
}

Osmmd::DatabaseConfiguration Osmmd::DatabaseConfiguration::FromBytes(const Bytes& bytes)
{
    DatabaseConfiguration config;

    rapidjson::Document document;
    std::string data(bytes.begin(), bytes.end());

    document.Parse(data.c_str());

    config.NAME = document[StringConstants::DatabaseConfiguration.NAME].GetString();

    for (auto& element : document[StringConstants::DatabaseConfiguration.TABLES].GetArray())
    {
        std::string tableName = element[StringConstants::DatabaseConfiguration.NAME].GetString();
        std::string tablePath = element[StringConstants::DatabaseConfiguration.PATH].GetString();

        config.TABLES.insert({ tableName, tablePath });
    }

    return config;
}

Osmmd::DatabaseConfiguration& Osmmd::DatabaseConfiguration::operator=(const DatabaseConfiguration& other)
{
    this->NAME = other.NAME;
    this->TABLES = other.TABLES;
    
    return *this;
}
