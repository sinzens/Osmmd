/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#include "Enum.h"
#include "StringConstants.h"

std::string Osmmd::GetDataTypeName(Osmmd::DataType type)
{
    switch (type)
    {
    case DataType::Integer:
        return StringConstants::DataType.INTEGER;
    case DataType::Char:
        return StringConstants::DataType.CHAR;
    }

    return StringConstants::DataType.UNKNOWN;
}

Osmmd::DataType Osmmd::GetDataType(const std::string& name)
{
    if (name == StringConstants::DataType.INTEGER)
    {
        return DataType::Integer;
    }

    if (name == StringConstants::DataType.CHAR)
    {
        return DataType::Char;
    }

    return DataType::Char;
}

std::string Osmmd::GetIndexStrategyName(Osmmd::IndexStrategy indexStrategy)
{
    switch (indexStrategy)
    {
    case IndexStrategy::BpTree:
        return StringConstants::IndexStrategy.BP_TREE;
    case IndexStrategy::Hash:
        return StringConstants::IndexStrategy.HASH;
    }

    return StringConstants::IndexStrategy.UNKNOWN;
}

Osmmd::IndexStrategy Osmmd::GetIndexStrategy(const std::string& name)
{
    if (name == StringConstants::IndexStrategy.BP_TREE)
    {
        return IndexStrategy::BpTree;
    }

    if (name == StringConstants::IndexStrategy.HASH)
    {
        return IndexStrategy::Hash;
    }

    return IndexStrategy::BpTree;
}
