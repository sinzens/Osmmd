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
    /*std::stringstream stream;

    stream << this->driver.size() << this->driver;

    for (auto& database : this->databases)
    {
        std::string databaseName = std::get<0>(database);
        std::string databasePath = std::get<1>(database);

        stream << databaseName.size() << databaseName;
        stream << databasePath.size() << databasePath;
    }

    return stream.str();*/

    rapidjson::Document document;
    document.SetObject();

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    document.AddMember("NAME", JsonString(this->NAME, allocator), allocator);

    rapidjson::Value databases(rapidjson::kArrayType);

    for (auto& database : this->DATABASES)
    {
        std::string databaseName = database.first;
        std::string databasePath = database.second;

        rapidjson::Value databaseObject(rapidjson::kObjectType);
        databaseObject.AddMember("NAME", JsonString(databaseName, allocator), allocator);
        databaseObject.AddMember("PATH", JsonString(databasePath, allocator), allocator);

        databases.PushBack(databaseObject, allocator);
    }

    document.AddMember("DATABASES", databases, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}

Osmmd::DriverConfiguration Osmmd::DriverConfiguration::FromBytes(const std::string& bytes)
{
    /*DriverConfiguration config;

    std::stringstream stream(bytes);

    int driverNameSize = 0;
    stream >> driverNameSize;

    char driverNameBuffer[100]{};

    stream.read(driverNameBuffer, driverNameSize);
    config.driver = driverNameBuffer;

    while (!stream.eof())
    {
        int databaseNameSize = 0, databasePathSize = 0;
        char databaseNameBuffer[100]{}, databasePathBuffer[256]{};

        stream >> databaseNameSize;
        if (databaseNameSize == 0) { break; }
        stream.read(databaseNameBuffer, databaseNameSize);

        stream >> databasePathSize;
        if (databasePathSize == 0) { break; }
        stream.read(databasePathBuffer, databasePathSize);

        config.databases.emplace_back(std::tuple(databaseNameBuffer, databasePathBuffer));
    }

    return config;*/

    DriverConfiguration config;

    rapidjson::Document document;
    document.Parse(bytes.c_str());

    config.NAME = document["NAME"].GetString();

    for (auto& element : document["DATABASES"].GetArray())
    {
        std::string databaseName = element["NAME"].GetString();
        std::string databasePath = element["PATH"].GetString();
        
        config.DATABASES.insert({ databaseName, databasePath });
    }

    return config;
}

Osmmd::DriverConfiguration& Osmmd::DriverConfiguration::operator=(const DriverConfiguration& other)
{
    /*this->driver = other.driver;
    this->databases = other.databases;*/

    this->NAME = other.NAME;
    this->DATABASES = other.DATABASES;

    return *this;
}
