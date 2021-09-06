/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
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

std::string Osmmd::GetCommandTypeName(CommandType type)
{
    switch (type)
    {
    case CommandType::CreateDatabase:
        return StringConstants::CommandType.CREATE_DATABASE;
    case CommandType::CreateTable:
        return StringConstants::CommandType.CREATE_TABLE;
    case CommandType::DeleteDatabase:
        return StringConstants::CommandType.DELETE_DATABASE;
    case CommandType::DeleteTable:
        return StringConstants::CommandType.DELETE_TABLE;
    case CommandType::Insert:
        return StringConstants::CommandType.INSERT;
    case CommandType::Delete:
        return StringConstants::CommandType.DELETE;
    case CommandType::Update:
        return StringConstants::CommandType.UPDATE;
    case CommandType::Select:
        return StringConstants::CommandType.SELECT;
    }

    return StringConstants::CommandType.UNKNOWN;
}

Osmmd::CommandType Osmmd::GetCommandType(const std::string& name)
{
    if (name == StringConstants::CommandType.CREATE_DATABASE)
    {
        return CommandType::CreateDatabase;
    }

    if (name == StringConstants::CommandType.CREATE_TABLE)
    {
        return CommandType::CreateTable;
    }

    if (name == StringConstants::CommandType.DELETE_DATABASE)
    {
        return CommandType::DeleteDatabase;
    }

    if (name == StringConstants::CommandType.DELETE_TABLE)
    {
        return CommandType::DeleteTable;
    }

    if (name == StringConstants::CommandType.INSERT)
    {
        return CommandType::Insert;
    }

    if (name == StringConstants::CommandType.DELETE)
    {
        return CommandType::Delete;
    }

    if (name == StringConstants::CommandType.UPDATE)
    {
        return CommandType::Update;
    }

    if (name == StringConstants::CommandType.SELECT)
    {
        return CommandType::Select;
    }

    return CommandType::Select;
}
