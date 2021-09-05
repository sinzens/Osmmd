/*
* Created by Zeng Yinuo, 2021.09.05
*/

#include "DataTableConfiguration.h"
#include "Value.h"
#include "Enum.h"

std::string Osmmd::DataTableConfiguration::ToString() const
{
    std::string result;

    char headerBuffer[255]{}, primaryKeyBuffer[255]{}, indexStrategyBuffer[50]{};

    sprintf_s(headerBuffer, "Table (%s):\n", this->NAME.c_str());
    sprintf_s(primaryKeyBuffer, "\tPrimary Key: %s\n", this->PRIMARY_KEY.c_str());
    sprintf_s(indexStrategyBuffer, "\tIndex Strategy: %s\n", GetIndexStrategyName(this->INDEX_STRATEGY).c_str());

    result.append(headerBuffer).append(primaryKeyBuffer).append(indexStrategyBuffer);
    result.append(std::string("\t") + "Indexes: (");
    
    for (auto i = this->INDEXES.begin(); i != this->INDEXES.end(); i++)
    {
        if (i != this->INDEXES.begin())
        {
            result.append(", ");
        }
        result.append((*i));
    }

    result.append(")");

    return result;
}

Bytes Osmmd::DataTableConfiguration::ToBytes() const
{
    Bytes bytes;

    Bytes nameLengthData = Value::FromInteger(static_cast<int32_t>(this->NAME.size())).GetBytes();
    Bytes nameData(this->NAME.begin(), this->NAME.end());
    Bytes primaryKeyLengthData = Value::FromInteger(static_cast<int32_t>(this->PRIMARY_KEY.size())).GetBytes();
    Bytes primaryKeyData(this->PRIMARY_KEY.begin(), this->PRIMARY_KEY.end());

    unsigned char indexStrategyData = static_cast<unsigned char>(this->INDEX_STRATEGY);

    Bytes indexIndexerCountData = Value::FromInteger(static_cast<int32_t>(this->INDEXES.size())).GetBytes();

    bytes.insert(bytes.end(), nameLengthData.begin(), nameLengthData.end());
    bytes.insert(bytes.end(), nameData.begin(), nameData.end());
    bytes.insert(bytes.end(), primaryKeyLengthData.begin(), primaryKeyLengthData.end());
    bytes.insert(bytes.end(), primaryKeyData.begin(), primaryKeyData.end());

    bytes.emplace_back(indexStrategyData);

    bytes.insert(bytes.end(), indexIndexerCountData.begin(), indexIndexerCountData.end());

    for (const std::string& index : this->INDEXES)
    {
        Bytes indexLengthData = Value::FromInteger(static_cast<int32_t>(index.size())).GetBytes();
        Bytes indexData(index.begin(), index.end());

        bytes.insert(bytes.end(), indexLengthData.begin(), indexLengthData.end());
        bytes.insert(bytes.end(), indexData.begin(), indexData.end());
    }

    Bytes dataLengthData = Value::FromInteger(static_cast<int32_t>(bytes.size())).GetBytes();
    bytes.insert(bytes.begin(), dataLengthData.begin(), dataLengthData.end());

    return bytes;
}

Osmmd::DataTableConfiguration Osmmd::DataTableConfiguration::FromBytes(const Bytes& bytes)
{
    auto nameLengthBegin = bytes.begin() + sizeof(int32_t);
    auto nameBegin = nameLengthBegin + sizeof(int32_t);

    int nameLength = Value::GetLengthFromBytesHead(Bytes(nameLengthBegin, nameBegin));

    auto primaryKeyLengthBegin = nameBegin + nameLength;
    auto primaryKeyBegin = primaryKeyLengthBegin + sizeof(int32_t);

    int primaryKeyLength = Value::GetLengthFromBytesHead(Bytes(primaryKeyLengthBegin, primaryKeyBegin));

    auto indexStrategyBegin = primaryKeyBegin + primaryKeyLength;
    auto indexIndexerCountBegin = indexStrategyBegin + sizeof(IndexStrategy);
    auto indexIndexerBegin = indexIndexerCountBegin + sizeof(int32_t);

    DataTableConfiguration config;

    config.NAME = std::string(nameBegin, primaryKeyLengthBegin);
    config.PRIMARY_KEY = std::string(primaryKeyBegin, indexStrategyBegin);
    config.INDEX_STRATEGY = static_cast<IndexStrategy>(bytes.at(indexStrategyBegin - bytes.begin()));
   
    int indexCount = Value::GetLengthFromBytesHead(Bytes(indexIndexerCountBegin, indexIndexerBegin));
    if (indexCount == 0)
    {
        return config;
    }

    int indexIndexerBeginIndex = indexIndexerBegin - bytes.begin();

    for (int i = 0; i < indexCount; i++)
    {
        auto indexIndexerLengthBegin = bytes.begin() + indexIndexerBeginIndex;
        auto indexIndexerDataBegin = indexIndexerLengthBegin + sizeof(int32_t);

        int indexIndexerLength = Value::GetLengthFromBytesHead(Bytes(indexIndexerLengthBegin, indexIndexerDataBegin));
        config.INDEXES.insert(std::string(indexIndexerDataBegin, indexIndexerDataBegin + indexIndexerLength));

        indexIndexerBeginIndex += sizeof(int32_t) + indexIndexerLength;
    }

    return config;
}

Osmmd::DataTableConfiguration& Osmmd::DataTableConfiguration::operator=(const DataTableConfiguration& other)
{
    this->NAME = other.NAME;
    this->PRIMARY_KEY = other.PRIMARY_KEY;
    this->INDEXES = other.INDEXES;

    this->INDEX_STRATEGY = other.INDEX_STRATEGY;

    return *this;
}
