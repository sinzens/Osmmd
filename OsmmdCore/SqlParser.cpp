/*
* Created by Zeng Yinuo, 2021.09.07
*/

#include "SqlParser.h"
#include "StringConstants.h"

#include "CreateDatabaseCommand.h"
#include "CreateTableCommand.h"
#include "DeleteDatabaseCommand.h"
#include "DeleteTableCommand.h"

#include "InsertCommand.h"
#include "DeleteCommand.h"
#include "UpdateCommand.h"
#include "SelectCommand.h"
#include "QuitCommand.h"

#include "Enum.h"

Osmmd::SqlParseResult Osmmd::SqlParser::Parse(const std::string& sql)
{
    return Parse(StringHelper(sql));
}

Osmmd::SqlParseResult Osmmd::SqlParser::Parse(const StringHelper& sql)
{
    StringHelper simplified = sql.Simplified().Removed(";");
    StringHelper lowercased = simplified.ToLowerCase();

    if (lowercased.GetString().empty())
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_COMMAND);
    }

    if (lowercased.StartsWith("q"))
    {
        return ParseQuitCommand(lowercased);
    }

    if (lowercased.StartsWith("create database"))
    {
        return ParseCreateDatabaseCommand(simplified);
    }

    if (lowercased.StartsWith("create table"))
    {
        return ParseCreateTableCommand(simplified);
    }

    if (lowercased.StartsWith("drop database"))
    {
        return ParseDeleteDatabaseCommand(simplified);
    }

    if (lowercased.StartsWith("drop table"))
    {
        return ParseDeleteTableCommand(simplified);
    }

    if (lowercased.StartsWith("insert into"))
    {
        return ParseInsertCommand(simplified);
    }

    if (lowercased.StartsWith("delete from"))
    {
        return ParseDeleteCommand(simplified);
    }

    if (lowercased.StartsWith("select"))
    {
        return ParseSelectCommand(simplified);
    }

    if (lowercased.StartsWith("update"))
    {
        return ParseUpdateCommand(simplified);
    }

    return NoSuchCommandResult(simplified);
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseQuitCommand(const StringHelper& sql)
{
    if (sql == "quit" || sql == "q")
    {
        return SqlParseResult(true, std::make_shared<QuitCommand>());
    }
    
    return NoSuchCommandResult(sql);
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseCreateDatabaseCommand(const StringHelper& sql)
{
    std::vector<std::string> tokens = sql.Split(" ");

    if (tokens.size() < 3)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATABASE_NAME);
    }

    StringHelper secondToken = StringHelper(tokens.at(1)).ToLowerCase();

    if (secondToken != "database")
    {
        return NoSuchCommandResult(StringHelper(std::string("create ").append(secondToken.GetString())));
    }

    StringHelper databaseName = StringHelper(tokens.at(2));
    std::string error = CheckIdentifierValid(databaseName);

    if (!error.empty())
    {
        return SqlParseResult(false, error);
    }

    return SqlParseResult
    (
        true,
        std::make_shared<CreateDatabaseCommand>(CreateDatabaseCommandArg(databaseName.GetString()))
    );
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseCreateTableCommand(const StringHelper& sql)
{
    if (sql.GetLength() <= 13 || sql.GetString().at(13) == '(')
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_NAME);
    }

    StringHelper afterCommand = sql.SubString(13).Trimmed();

    size_t definitionBegin = afterCommand.GetString().find_first_of("(");

    if (definitionBegin == std::string::npos)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_DEFINITION);
    }

    size_t definitionEnd = afterCommand.GetString().find_last_of(")");

    if (definitionEnd == std::string::npos)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_DEFINITION_END);
    }

    IndexStrategy indexStrategy = IndexStrategy::Hash;

    if (definitionEnd != static_cast<size_t>(afterCommand.GetLength()) - 1)
    {
        StringHelper indexStrategyStr = afterCommand.SubString(definitionEnd + 1).Trimmed();

        if (!IsKnownIndexStrategy(indexStrategyStr.GetString()))
        {
            return UnknownIndexStrategyResult(indexStrategyStr);
        }

        indexStrategy = GetIndexStrategy(indexStrategyStr.GetString());
    }  

    StringHelper tableName = afterCommand.SubString(0, definitionBegin).Trimmed();
    std::string tableNameError = CheckIdentifierValid(tableName);

    if (!tableNameError.empty())
    {
        return SqlParseResult(false, tableNameError);
    }

    StringHelper definition = afterCommand.SubString(definitionBegin, definitionEnd + 1).Trimmed();

    if (definition.GetLength() <= 2)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_DEFINITION_CONTENT);
    }

    StringHelper definitionContent = definition.SubString(1, definition.GetLength() - 1).Trimmed();
    std::vector<std::string> declarations = SplitCreateTableDeclarations(definitionContent.GetString());

    Row rowDefinition;
    DataTableConfiguration config;

    std::string primaryKeyName;
    std::set<std::string> indexNames;

    for (const std::string& declarationStr : declarations)
    {
        if (declarationStr.empty())
        {
            continue;
        }

        StringHelper declaration = StringHelper(declarationStr).Trimmed();
        StringHelper lowercased = declaration.ToLowerCase();

        if (lowercased.StartsWith("primary key"))
        {
            StringHelper primaryKey = lowercased.Removed("primary key");
            
            size_t primaryKeyBegin = primaryKey.GetString().find_first_of("(");
            size_t primaryKeyEnd = primaryKey.GetString().find_first_of(")");

            if (primaryKeyBegin == std::string::npos || primaryKeyEnd == std::string::npos || (primaryKeyEnd - primaryKeyBegin) < 2)
            {
                return SqlParseResult(false, StringConstants::Error.SQL_INVALID_PRIMARY_KEY_DECLARATION);
            }

            primaryKeyName = primaryKey.SubString(primaryKeyBegin + 1, primaryKeyEnd).GetString();

            continue;
        }

        if (lowercased.StartsWith("index"))
        {
            StringHelper indexStr = lowercased.Removed("index");

            size_t indexBegin = indexStr.GetString().find_first_of("(");
            size_t indexEnd = indexStr.GetString().find_first_of(")");

            if (indexBegin == std::string::npos || indexEnd == std::string::npos || (indexEnd - indexBegin) < 2)
            {
                return SqlParseResult(false, StringConstants::Error.SQL_INVALID_INDEX_DECLARATION);
            }

            StringHelper indexesStr = indexStr.SubString(indexBegin + 1, indexEnd).Trimmed();

            if (!indexesStr.Contains(","))
            {
                indexNames.insert(indexesStr.GetString());
                continue;
            }

            std::vector<std::string> indexes = indexesStr.Split(",");

            for (const std::string& index : indexes)
            {
                indexNames.insert(StringHelper(index).Trimmed().GetString());
            }

            continue;
        }

        std::vector<std::string> tokens = declaration.Split(" ");

        if (tokens.size() < 2)
        {
            return SqlParseResult(false, StringConstants::Error.SQL_INVALID_COLUMN_DEFINITION);
        }

        StringHelper columnName = StringHelper(tokens.at(0)).Trimmed();
        std::string error = CheckIdentifierValid(columnName);

        if (!error.empty())
        {
            return SqlParseResult(false, error);
        }

        StringHelper typeStr = StringHelper(tokens.at(1)).ToLowerCase().Trimmed();

        size_t typeLengthBegin = typeStr.GetString().find_first_of("(");
        size_t typeLengthEnd = typeStr.GetString().find_first_of(")");

        StringHelper typeName, typeLengthStr;

        if (typeLengthBegin == std::string::npos && typeLengthEnd == std::string::npos)
        {
            typeName = typeStr;
        }
        else if (typeLengthBegin != std::string::npos && typeLengthEnd != std::string::npos)
        {
            typeName = typeStr.SubString(0, typeLengthBegin).Trimmed();
            typeLengthStr = typeStr.SubString(typeLengthBegin, typeLengthEnd + 1).Trimmed();
        }
        else
        {
            return SqlParseResult(false, StringConstants::Error.SQL_INVALID_COLUMN_DEFINITION);
        }

        if (!IsKnownDataType(typeName.GetString()))
        {
            return UnknownTypeResult(typeName);
        }

        DataType type = GetDataType(typeName.GetString());

        if (typeLengthStr.GetLength() == 0 && type == DataType::Char)
        {
            return SqlParseResult(false, StringConstants::Error.SQL_CHAR_NO_LENGTH);
        }

        if (typeLengthStr.GetLength() <= 2)
        {
            return SqlParseResult(false, StringConstants::Error.SQL_LENGTH_EMPTY);
        }

        StringHelper lengthContent = typeLengthStr.SubString(1, typeLengthStr.GetLength() - 1).Trimmed();

        int length = 0;

        switch (type)
        {
        case DataType::Integer:
            length = sizeof(int32_t);
            break;
        case DataType::Char:
            length = atoi(lengthContent.GetString().c_str());
            break;
        case DataType::Double:
            length = sizeof(double);
            break;
        case DataType::DateTime:
            length = sizeof(int16_t) + 5 * sizeof(int8_t);
            break;
        }

        rowDefinition.AddColumn(Column(columnName.GetString(), length, type));
    }

    if (primaryKeyName.empty())
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_PRIMARY_KEY);
    }

    if (rowDefinition.Columns.size() == 0)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_COLUMNS);
    }

    if (!rowDefinition.HasColumn(primaryKeyName))
    {
        return ColumnNotExistResult(StringHelper(primaryKeyName), tableName);
    }

    for (const std::string& indexName : indexNames)
    {
        if (!rowDefinition.HasColumn(indexName))
        {
            return ColumnNotExistResult(StringHelper(indexName), tableName);
        }
    }

    config.NAME = tableName.GetString();
    config.PRIMARY_KEY = primaryKeyName;
    config.INDEXES = indexNames;
    config.INDEX_STRATEGY = indexStrategy;

    return SqlParseResult
    (
        true,
        std::make_shared<CreateTableCommand>(CreateTableCommandArg(config, rowDefinition))
    );
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseDeleteDatabaseCommand(const StringHelper& sql)
{
    std::vector<std::string> tokens = sql.Split(" ");

    if (tokens.size() < 3)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATABASE_NAME);
    }

    StringHelper secondToken = StringHelper(tokens.at(1)).ToLowerCase();

    if (secondToken != "database")
    {
        return NoSuchCommandResult(StringHelper(std::string("drop ").append(secondToken.GetString())));
    }

    return SqlParseResult
    (
        true,
        std::make_shared<DeleteDatabaseCommand>(DeleteDatabaseCommandArg(tokens.at(2)))
    );
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseDeleteTableCommand(const StringHelper& sql)
{
    std::vector<std::string> tokens = sql.Split(" ");

    if (tokens.size() < 3)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_NAME);
    }

    StringHelper secondToken = StringHelper(tokens.at(1)).ToLowerCase();

    if (secondToken != "table")
    {
        return NoSuchCommandResult(StringHelper(std::string("drop ").append(secondToken.GetString())));
    }

    return SqlParseResult
    (
        true,
        std::make_shared<DeleteTableCommand>(DeleteTableCommandArg(tokens.at(2)))
    );
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseInsertCommand(const StringHelper& sql)
{
    std::vector<std::string> tokens = sql.ToLowerCase().Split(" ");

    if (tokens.at(1) != "into")
    {
        return NoSuchCommandResult(StringHelper(std::string("insert ").append(tokens.at(1))));
    }

    if (tokens.size() < 3)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_NAME);
    }

    StringHelper tableName = StringHelper(tokens.at(2)).Trimmed();

    if (tableName.GetLength() == 0)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_NAME);
    }

    size_t valueBegin = sql.ToLowerCase().GetString().find("values(");
    size_t valueEnd = sql.GetString().find_last_of(")");

    if (valueBegin == std::string::npos)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_INSERT_VALUES);
    }

    if (valueEnd == std::string::npos)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_INSERT_VALUES_END);
    }

    size_t valueTrueBegin = sql.GetString().find_first_of("(");

    if (valueEnd - valueTrueBegin < 2)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_INSERT_VALUES);
    }

    std::vector<std::shared_ptr<ColumnValue>> columnValues;

    StringHelper valueContent = sql.SubString(valueTrueBegin + 1, valueEnd).Trimmed();
    std::vector<std::string> values = valueContent.Split(",");

    for (const std::string& value : values)
    {
        StringHelper valueStr = StringHelper(value).Trimmed();

        if ((valueStr.StartsWith("'") && !valueStr.EndsWith("'")) || (!valueStr.StartsWith("'") && valueStr.EndsWith("'")))
        {
            return SqlParseResult(false, StringConstants::Error.SQL_INVALID_CHAR_VALUE_FORMAT);
        }

        if (valueStr.Contains("\""))
        {
            return SqlParseResult(false, StringConstants::Error.SQL_INVALID_CHAR_VALUE_FORMAT);
        }

        columnValues.emplace_back(ParseValue(valueStr));
    }

    std::shared_ptr<RowValue> rowValue = std::make_shared<RowValue>(columnValues);

    return SqlParseResult
    (
        true,
        std::make_shared<InsertCommand>(InsertCommandArg(tableName.GetString(), rowValue))
    );
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseDeleteCommand(const StringHelper& sql)
{
    return SqlParseResult();
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseUpdateCommand(const StringHelper& sql)
{
    return SqlParseResult();
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseSelectCommand(const StringHelper& sql)
{
    return SqlParseResult();
}

Osmmd::SqlParseResult Osmmd::SqlParser::NoSuchCommandResult(const StringHelper& command)
{
    char buffer[100]{};
    sprintf_s(buffer, "%s '%s'", StringConstants::Error.SQL_NO_SUCH_COMMAND, command.GetString().c_str());

    return SqlParseResult(false, buffer);
}

Osmmd::SqlParseResult Osmmd::SqlParser::UnknownIndexStrategyResult(const StringHelper& indexStrategy)
{
    char buffer[100]{};
    sprintf_s(buffer, "%s '%s'", StringConstants::Error.SQL_UNKNOWN_INDEX_STRATEGY, indexStrategy.GetString().c_str());

    return SqlParseResult(false, buffer);
}

Osmmd::SqlParseResult Osmmd::SqlParser::UnknownTypeResult(const StringHelper& type)
{
    char buffer[100]{};
    sprintf_s(buffer, "%s '%s'", StringConstants::Error.SQL_UNKNOWN_TYPE, type.GetString().c_str());

    return SqlParseResult(false, buffer);
}

Osmmd::SqlParseResult Osmmd::SqlParser::ColumnNotExistResult(const StringHelper& columnName, const StringHelper& tableName)
{
    char buffer[100]{};
    sprintf_s
    (
        buffer,
        "Column '%s' doesn't exist in table '%s'",
        columnName.GetString().c_str(),
        tableName.GetString().c_str()
    );

    return SqlParseResult(false, buffer);
}

std::string Osmmd::SqlParser::CheckIdentifierValid(const StringHelper& identifier)
{
    if (identifier.GetLength() < 2)
    {
        return StringConstants::Error.SQL_INVALID_IDENTIFIER_TOO_SHORT;
    }

    if (identifier.StartsWithNumber())
    {
        return StringConstants::Error.SQL_INVALID_IDENTIFIER_STARTS_WITH_NUMBER;
    }

    if (!identifier.ContainsOnlyLettersNumbersAndUnderscore())
    {
        return StringConstants::Error.SQL_INVALID_IDENTIFIER_NOT_ALLOWED_CHARACTER;
    }

    return std::string();
}

std::vector<std::string> Osmmd::SqlParser::SplitCreateTableDeclarations(const std::string declaration)
{
    std::vector<std::string> results;

    int bracketCounter = 0;
    size_t lastCommaIndex = -1;

    for (auto i = declaration.begin(); i != declaration.end(); i++)
    {
        if (i == declaration.end() - 1)
        {
            size_t currentIndex = i - declaration.begin();
            results.emplace_back(declaration.substr(lastCommaIndex + 1, currentIndex - lastCommaIndex));
        }

        char ch = (*i);

        if (ch == '(')
        {
            bracketCounter++;
            continue;
        }

        if (ch == ')')
        {
            bracketCounter--;
            continue;
        }

        if (ch == ',' && bracketCounter == 0)
        {
            size_t currentIndex = i - declaration.begin();
            results.emplace_back(declaration.substr(lastCommaIndex + 1, currentIndex - lastCommaIndex - 1));

            lastCommaIndex = currentIndex;
        }
    }

    if (results.size() == 0)
    {
        results.emplace_back(declaration);
    }

    return results;
}

Osmmd::DataType Osmmd::SqlParser::ParseType(const StringHelper& str)
{
    if (str.StartsWith("'") && str.EndsWith("'"))
    {
        int year, month, day, hour, minute, second;
        int successful = sscanf_s
        (
            str.GetString().c_str(),
            "%04d-%02d-%02d %02d:%02d:%02d",
            &year,
            &month,
            &day,
            &hour,
            &minute,
            &second
        );

        return successful == 6 ? DataType::DateTime : DataType::Char;
    }

    if (str.IsDouble(true))
    {
        return DataType::Double;
    }

    if (str.ContainsOnlyNumbers())
    {
        return DataType::Integer;
    }

    return DataType::Char;
}

std::shared_ptr<Osmmd::ColumnValue> Osmmd::SqlParser::ParseValue(const StringHelper& str)
{
    DataType type = ParseType(str);
    Value value;

    switch (type)
    {
    case DataType::Integer:
        value = Value::FromInteger(atoi(str.GetString().c_str()));
        break;
    case DataType::Char:
        value = Value::FromChar(str.Removed("'").GetString());
        break;
    case DataType::Double:
        value = Value::FromDouble(atof(str.GetString().c_str()));
        break;
    case DataType::DateTime:
        value = Value::FromDateTime(DateTime::FromString(str.Removed("'").GetString()));
        break;
    }

    return std::make_shared<ColumnValue>(value);
}
