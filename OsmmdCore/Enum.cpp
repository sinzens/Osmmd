/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "Enum.h"
#include "StringConstants.h"
#include "StringHelper.h"

std::string Osmmd::GetDataTypeName(Osmmd::DataType type)
{
    switch (type)
    {
    case DataType::Integer:
        return StringConstants::DataType.INTEGER;
    case DataType::Char:
        return StringConstants::DataType.CHAR;
    case DataType::Double:
        return StringConstants::DataType.DOUBLE;
    case DataType::DateTime:
        return StringConstants::DataType.DATETIME;
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

    if (name == StringConstants::DataType.DOUBLE)
    {
        return DataType::Double;
    }

    if (name == StringConstants::DataType.DATETIME)
    {
        return DataType::DateTime;
    }

    return DataType::Char;
}

bool Osmmd::IsKnownDataType(const std::string& name)
{
    return
    (
        name == StringConstants::DataType.INTEGER ||
        name == StringConstants::DataType.CHAR ||
        name == StringConstants::DataType.DOUBLE ||
        name == StringConstants::DataType.DATETIME
    );
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
    if (StringHelper(StringConstants::IndexStrategy.BP_TREE).ToLowerCase() == name)
    {
        return IndexStrategy::BpTree;
    }

    if (StringHelper(StringConstants::IndexStrategy.HASH).ToLowerCase() == name)
    {
        return IndexStrategy::Hash;
    }

    return IndexStrategy::Hash;
}

bool Osmmd::IsKnownIndexStrategy(const std::string& name)
{
    StringHelper lowercased = StringHelper(name).ToLowerCase();

    return
    (
        StringHelper(StringConstants::IndexStrategy.BP_TREE).ToLowerCase() == lowercased ||
        StringHelper(StringConstants::IndexStrategy.HASH).ToLowerCase() == lowercased
    );
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
    case CommandType::UseDatabase:
        return StringConstants::CommandType.USE_DATABASE;
    case CommandType::Quit:
        return StringConstants::CommandType.QUIT;
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

    if (name == StringConstants::CommandType.USE_DATABASE)
    {
        return CommandType::UseDatabase;
    }

    if (name == StringConstants::CommandType.QUIT)
    {
        return CommandType::Quit;
    }

    return CommandType::Select;
}

std::string Osmmd::GetConditionOperatorName(ConditionOperator opt)
{
    switch (opt)
    {
    case ConditionOperator::Equal:
        return StringConstants::ConditionOperator.EQUAL;
    case ConditionOperator::NotEqual:
        return StringConstants::ConditionOperator.NOT_EQUAL1;
    case ConditionOperator::LessThan:
        return StringConstants::ConditionOperator.LESS_THAN;
    case ConditionOperator::GreaterThan:
        return StringConstants::ConditionOperator.GREATER_THAN;
    case ConditionOperator::LessThanEqual:
        return StringConstants::ConditionOperator.LESS_THAN_EQUAL;
    case ConditionOperator::GreaterThanEqual:
        return StringConstants::ConditionOperator.GREATER_THAN_EQUAL;
    }

    return StringConstants::ConditionOperator.UNKNOWN;
}

Osmmd::ConditionOperator Osmmd::GetConditionOperator(const std::string& name)
{
    if (name == StringConstants::ConditionOperator.EQUAL)
    {
        return ConditionOperator::Equal;
    }

    if (name == StringConstants::ConditionOperator.NOT_EQUAL1 || name == StringConstants::ConditionOperator.NOT_EQUAL2)
    {
        return ConditionOperator::NotEqual;
    }

    if (name == StringConstants::ConditionOperator.LESS_THAN)
    {
        return ConditionOperator::LessThan;
    }

    if (name == StringConstants::ConditionOperator.GREATER_THAN)
    {
        return ConditionOperator::GreaterThan;
    }

    if (name == StringConstants::ConditionOperator.LESS_THAN_EQUAL)
    {
        return ConditionOperator::LessThanEqual;
    }

    if (name == StringConstants::ConditionOperator.GREATER_THAN_EQUAL)
    {
        return ConditionOperator::GreaterThanEqual;
    }

    return ConditionOperator::Equal;
}

bool Osmmd::IsKnownConditionOperator(const std::string& name)
{
    return
    (
        name == StringConstants::ConditionOperator.EQUAL ||
        name == StringConstants::ConditionOperator.NOT_EQUAL1 ||
        name == StringConstants::ConditionOperator.NOT_EQUAL2 ||
        name == StringConstants::ConditionOperator.LESS_THAN ||
        name == StringConstants::ConditionOperator.GREATER_THAN ||
        name == StringConstants::ConditionOperator.LESS_THAN_EQUAL ||
        name == StringConstants::ConditionOperator.GREATER_THAN_EQUAL
    );
}

Osmmd::ConditionOperator Osmmd::GetInvertedConditionOperator(ConditionOperator opt)
{
    switch (opt)
    {
    case ConditionOperator::LessThan:
        return ConditionOperator::GreaterThan;
    case ConditionOperator::GreaterThan:
        return ConditionOperator::LessThan;
    case ConditionOperator::LessThanEqual:
        return ConditionOperator::GreaterThanEqual;
    case ConditionOperator::GreaterThanEqual:
        return ConditionOperator::LessThanEqual;
    }

    return opt;
}

Osmmd::ConditionOperator Osmmd::GetOppositeConditionOperator(ConditionOperator opt)
{
    switch (opt)
    {
    case ConditionOperator::Equal:
        return ConditionOperator::NotEqual;
    case ConditionOperator::NotEqual:
        return ConditionOperator::Equal;
    case ConditionOperator::LessThan:
        return ConditionOperator::GreaterThanEqual;
    case ConditionOperator::GreaterThan:
        return ConditionOperator::LessThanEqual;
    case ConditionOperator::LessThanEqual:
        return ConditionOperator::GreaterThan;
    case ConditionOperator::GreaterThanEqual:
        return ConditionOperator::LessThan;
    }

    return opt;
}
