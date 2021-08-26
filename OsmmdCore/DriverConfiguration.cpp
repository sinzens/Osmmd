/*
* Created by Zeng Yinuo, 2021.08.26
*/

#include "DriverConfiguration.h"
#include "StringConstants.h"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>

static rapidjson::Value JsonString(const std::string& str, rapidjson::MemoryPoolAllocator<>& allocator)
{
    rapidjson::Value value;
    value.SetString(str.c_str(), str.length(), allocator);
    return value;
}

std::string Osmmd::DriverConfiguration::ToBytes() const
{
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    document.AddMember(StringConstants::DriverConfiguration.NAME, JsonString(this->NAME, allocator), allocator);

    rapidjson::Value databases(rapidjson::kArrayType);

    for (auto& database : this->DATABASES)
    {
        std::string databaseName = database.first;
        std::string databasePath = database.second;

        rapidjson::Value databaseObject(rapidjson::kObjectType);
        databaseObject.AddMember(StringConstants::DriverConfiguration.NAME, JsonString(databaseName, allocator), allocator);
        databaseObject.AddMember(StringConstants::DriverConfiguration.PATH, JsonString(databasePath, allocator), allocator);

        databases.PushBack(databaseObject, allocator);
    }

    document.AddMember(StringConstants::DriverConfiguration.DATABASES, databases, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}

Osmmd::DriverConfiguration Osmmd::DriverConfiguration::FromBytes(const std::string& bytes)
{
    DriverConfiguration config;

    rapidjson::Document document;
    document.Parse(bytes.c_str());

    config.NAME = document[StringConstants::DriverConfiguration.NAME].GetString();

    for (auto& element : document[StringConstants::DriverConfiguration.DATABASES].GetArray())
    {
        std::string databaseName = element[StringConstants::DriverConfiguration.NAME].GetString();
        std::string databasePath = element[StringConstants::DriverConfiguration.PATH].GetString();
        
        config.DATABASES.insert({ databaseName, databasePath });
    }

    return config;
}

Osmmd::DriverConfiguration& Osmmd::DriverConfiguration::operator=(const DriverConfiguration& other)
{
    this->NAME = other.NAME;
    this->DATABASES = other.DATABASES;

    return *this;
}
