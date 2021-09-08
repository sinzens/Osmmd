/*
* Created by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
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

#include "UseDatabaseCommand.h"
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

    if (lowercased.StartsWith("use"))
    {
        return ParseUseDatabaseCommand(simplified);
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

    if (tokens.size() > 3)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_TOO_MANY_ARGS);
    }

    StringHelper secondToken = StringHelper(tokens.at(1)).ToLowerCase();

    if (secondToken != "database")
    {
        return NoSuchCommandResult(StringHelper(std::string("drop ").append(secondToken.GetString())));
    }

    std::string databaseName = StringHelper(tokens.at(2)).Trimmed().GetString();

    return SqlParseResult
    (
        true,
        std::make_shared<DeleteDatabaseCommand>(DeleteDatabaseCommandArg(databaseName))
    );
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseDeleteTableCommand(const StringHelper& sql)
{
    std::vector<std::string> tokens = sql.Split(" ");

    if (tokens.size() < 3)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_NAME);
    }

    if (tokens.size() > 3)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_TOO_MANY_ARGS);
    }

    StringHelper secondToken = StringHelper(tokens.at(1)).ToLowerCase();

    if (secondToken != "table")
    {
        return NoSuchCommandResult(StringHelper(std::string("drop ").append(secondToken.GetString())));
    }

    std::string tableName = StringHelper(tokens.at(2)).Trimmed().GetString();

    return SqlParseResult
    (
        true,
        std::make_shared<DeleteTableCommand>(DeleteTableCommandArg(tableName))
    );
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseUseDatabaseCommand(const StringHelper& sql)
{
    std::vector<std::string> tokens = sql.Split(" ");

    if (tokens.size() < 2)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATABASE_NAME);
    }

    if (tokens.size() > 2)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_TOO_MANY_ARGS);
    }

    if (StringHelper(tokens.front()).ToLowerCase() != "use")
    {
        return NoSuchCommandResult(StringHelper(tokens.front()));
    }

    std::string databaseName = StringHelper(tokens.at(1)).Trimmed().GetString();

    return SqlParseResult
    (
        true,
        std::make_shared<UseDatabaseCommand>(UseDatabaseCommandArg(databaseName))
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

    size_t valueTrueBegin = sql.GetString().find_first_of("(", valueBegin);

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
    std::vector<std::string> tokens = sql.ToLowerCase().Split(" ");

    if (tokens.at(1) != "from")
    {
        return NoSuchCommandResult(StringHelper(std::string("delete ").append(tokens.at(1))));
    }

    if (tokens.size() < 3)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_NAME);
    }

    StringHelper tableName = StringHelper(tokens.at(2)).Trimmed();

    if (tableName.GetLength() == 0 || tableName == "where")
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_NAME);
    }

    tableName = StringHelper(sql.Split(" ").at(2)).Trimmed();

    size_t conditionsBegin = sql.ToLowerCase().GetString().find("where");
    
    if (conditionsBegin == std::string::npos)
    {
        return SqlParseResult(false, std::make_shared<DeleteCommand>(DeleteCommandArg(tableName.GetString(), {})));
    }

    size_t conditionsTrueBegin = sql.GetString().find_first_not_of(" ", conditionsBegin + 5);

    if (conditionsTrueBegin == std::string::npos)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_CONDITIONS);
    }
    
    std::string error;
    StringHelper conditionsStr = sql.SubString(conditionsTrueBegin).Trimmed();

    std::vector<Condition> conditions = ParseConditions(conditionsStr, error);

    if (!error.empty())
    {
        return SqlParseResult(false, error);
    }

    return SqlParseResult
    (
        true,
        std::make_shared<DeleteCommand>(DeleteCommandArg(tableName.GetString(), conditions))
    );
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseUpdateCommand(const StringHelper& sql)
{
    StringHelper lowercased = sql.ToLowerCase();
    std::vector<std::string> tokens = lowercased.Split(" ");

    if (tokens.at(0) != "update")
    {
        return NoSuchCommandResult(StringHelper(tokens.at(0)));
    }

    if (tokens.size() < 2)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_NAME);
    }

    StringHelper tableName = StringHelper(tokens.at(1)).Trimmed();

    if (tableName.GetLength() == 0 || tableName == "set")
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_NAME);
    }

    tableName = StringHelper(sql.Split(" ").at(1)).Trimmed();

    if (!lowercased.Contains(" set "))
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_UPDATE_VALUES);
    }

    size_t conditionsBegin = lowercased.IndexOf("where");
    size_t updateValuesBegin = static_cast<size_t>(lowercased.IndexOf(" set ")) + 5;
    size_t updateValuesEnd = sql.GetLength();

    if (updateValuesBegin >= sql.GetLength())
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_UPDATE_VALUES);
    }

    if (conditionsBegin != std::string::npos)
    {
        updateValuesEnd = conditionsBegin;
    }

    Row updateRow;
    std::shared_ptr<RowValue> updateValue = std::make_shared<RowValue>();

    StringHelper updateValuesStr = sql.SubString(updateValuesBegin, updateValuesEnd);
    std::vector<std::string> values = SplitUpdateValues(updateValuesStr.GetString());

    for (const std::string& value : values)
    {
        std::vector<std::string> columnAndValue = StringHelper(value).Trimmed().Split("=");

        if (columnAndValue.size() != 2)
        {
            return SqlParseResult(false, StringConstants::Error.SQL_INVALID_EXPRESSION);
        }

        StringHelper columnName = StringHelper(columnAndValue.front()).Trimmed();
        StringHelper valueStr = StringHelper(columnAndValue.back()).Trimmed();

        std::string error = CheckIdentifierValid(columnName);

        if (!error.empty())
        {
            return SqlParseResult(false, error);
        }

        std::shared_ptr<ColumnValue> columnValue = ParseValue(valueStr);

        updateValue->Values.emplace_back(columnValue);
        updateRow.AddColumn(Column(columnName.GetString(), columnValue->GetLength(), columnValue->GetType()));
    }

    std::vector<Condition> conditions;

    if (conditionsBegin != std::string::npos)
    {
        size_t conditionsTrueBegin = sql.GetString().find_first_not_of(" ", conditionsBegin + 5);

        if (conditionsTrueBegin == std::string::npos)
        {
            return SqlParseResult(false, StringConstants::Error.SQL_NO_CONDITIONS);
        }

        std::string error;
        StringHelper conditionsStr = sql.SubString(conditionsTrueBegin).Trimmed();

        conditions = ParseConditions(conditionsStr, error);

        if (!error.empty())
        {
            return SqlParseResult(false, error);
        }
    }

    return SqlParseResult
    (
        true,
        std::make_shared<UpdateCommand>(UpdateCommandArg(tableName.GetString(), conditions, updateRow, updateValue))
    );
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseSelectCommand(const StringHelper& sql)
{
    StringHelper lowercased = sql.ToLowerCase();
    std::vector<std::string> tokens = lowercased.Split(" ");

    if (tokens.at(0) != "select")
    {
        return NoSuchCommandResult(StringHelper(tokens.at(0)));
    }

    size_t fromBegin = lowercased.IndexOf("from");

    if (fromBegin == std::string::npos)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_NAME);
    }

    size_t fromTrueBegin = fromBegin + 4;

    if (fromTrueBegin >= sql.GetLength())
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_NAME);
    }

    size_t conditionsBegin = lowercased.IndexOf("where");
    size_t fromEnd = sql.GetLength();

    if (conditionsBegin != std::string::npos)
    {
        fromEnd = conditionsBegin;
    }

    StringHelper tableName = sql.SubString(fromTrueBegin, fromEnd).Trimmed();
    StringHelper selectRowStr = sql.SubString(6, fromBegin).Trimmed();

    std::vector<std::string> names = selectRowStr.Split(",");
    std::vector<std::string> columnNames;

    for (const std::string& name : names)
    {
        columnNames.emplace_back(StringHelper(name).Trimmed().GetString());
    }

    for (const std::string& name : columnNames)
    {
        std::cout << name << std::endl;
    }

    std::vector<Condition> conditions;

    if (conditionsBegin != std::string::npos)
    {
        size_t conditionsTrueBegin = sql.GetString().find_first_not_of(" ", conditionsBegin + 5);

        if (conditionsTrueBegin == std::string::npos)
        {
            return SqlParseResult(false, StringConstants::Error.SQL_NO_CONDITIONS);
        }

        std::string error;
        StringHelper conditionsStr = sql.SubString(conditionsTrueBegin).Trimmed();

        conditions = ParseConditions(conditionsStr, error);

        if (!error.empty())
        {
            return SqlParseResult(false, error);
        }
    }

    return SqlParseResult
    (
        true,
        std::make_shared<SelectCommand>(SelectCommandArg(tableName.GetString(), conditions, columnNames))
    );
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

std::vector<std::string> Osmmd::SqlParser::SplitCreateTableDeclarations(const std::string& declaration)
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

std::vector<std::string> Osmmd::SqlParser::SplitConditions(const std::string& conditions)
{
    std::vector<std::string> results;

    StringHelper conditionsStr = StringHelper(conditions).Trimmed();
    StringHelper lowercased = conditionsStr.ToLowerCase();

    if (!lowercased.Contains(" and "))
    {
        results.emplace_back(conditionsStr.GetString());
        return results;
    }

    std::vector<std::string> splitted = lowercased.Split(" and ");

    for (const std::string& split : splitted)
    {
        size_t matchedStart = lowercased.IndexOf(split);
        std::string condition = conditionsStr.GetString().substr(matchedStart, split.size());

        results.emplace_back(condition);
    }

    if (results.size() == 0)
    {
        results.emplace_back(conditions);
    }

    return results;
}

std::vector<std::string> Osmmd::SqlParser::SplitUpdateValues(const std::string& values)
{
    std::vector<std::string> results = StringHelper(values).Split(",");

    if (results.size() == 0)
    {
        results.emplace_back(values);
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

std::vector<Osmmd::Condition> Osmmd::SqlParser::ParseConditions(const StringHelper& str, std::string& error)
{
    std::vector<Condition> conditions;

    if (str.ToLowerCase().Contains(" or "))
    {
        error = StringConstants::Error.SQL_OR_NOT_SUPPORTED;
        return conditions;
    }

    std::vector<std::string> conditionStrs = SplitConditions(str.GetString());

    for (const std::string& conditionStr : conditionStrs)
    {
        std::string conditionError;
        Condition condition = ParseCondition(StringHelper(conditionStr).Trimmed(), conditionError);

        if (!conditionError.empty())
        {
            error = conditionError;
            return conditions;
        }

        conditions.emplace_back(condition);
    }

    return conditions;
}

Osmmd::Condition Osmmd::SqlParser::ParseCondition(const StringHelper& str, std::string& error)
{
    static const std::set<char> operatorBegins = { '=', '!', '<', '>' };

    size_t operatorBegin = -1;

    for (auto i = str.GetString().begin(); i != str.GetString().end(); i++)
    {
        char ch = (*i);

        if (operatorBegins.find(ch) != operatorBegins.end())
        {
            if (operatorBegin == -1)
            {
                operatorBegin = i - str.GetString().begin();
            }

            continue;
        }

        if (operatorBegin == -1)
        {
            continue;
        }

        StringHelper left = str.SubString(0, operatorBegin).Trimmed();

        if (left.GetLength() == 0)
        {
            error = StringConstants::Error.SQL_INVALID_EXPRESSION;
            return Condition();
        }

        size_t operatorEnd = i - str.GetString().begin();
        StringHelper right = str.SubString(operatorEnd).Trimmed();

        if (right.GetLength() == 0)
        {
            error = StringConstants::Error.SQL_INVALID_EXPRESSION;
            return Condition();
        }

        std::string optStr = str.SubString(operatorBegin, operatorEnd).GetString();

        if (!IsKnownConditionOperator(optStr))
        {
            char buffer[30]{};
            sprintf_s(buffer, "%s '%s'", StringConstants::Error.SQL_UNKNOWN_OPERATOR, optStr.c_str());

            error = buffer;
            return Condition();
        }

        ConditionOperator opt = GetConditionOperator(optStr);

        bool leftIsColumn = IsColumnName(left);
        bool rightIsColumn = IsColumnName(right);

        if (leftIsColumn && rightIsColumn)
        {
            std::string leftError = CheckIdentifierValid(left);
            std::string rightError = CheckIdentifierValid(right);

            if (!leftError.empty())
            {
                error = leftError;
                return Condition();
            }

            if (!rightError.empty())
            {
                error = rightError;
                return Condition();
            }

            return Condition
            (
                opt,
                std::vector<std::string>({ left.GetString(), right.GetString() }),
                nullptr
            );
        }
        else if (!leftIsColumn && !rightIsColumn)
        {
            return Condition(opt, std::vector<std::string>(), nullptr);
        }
        else
        {
            if (leftIsColumn)
            {
                std::string columnError = CheckIdentifierValid(left);

                if (!columnError.empty())
                {
                    error = columnError;
                    return Condition();
                }

                return Condition
                (
                    opt,
                    std::vector<std::string>({ left.GetString() }),
                    ParseValue(right)
                );
            }

            if (rightIsColumn)
            {
                std::string columnError = CheckIdentifierValid(right);

                if (!columnError.empty())
                {
                    error = columnError;
                    return Condition();
                }

                return Condition
                (
                    GetInvertedConditionOperator(opt),
                    std::vector<std::string>({ right.GetString() }),
                    ParseValue(left)
                );
            }
        }
    }

    error = StringConstants::Error.SQL_INVALID_EXPRESSION;
    return Condition();
}

bool Osmmd::SqlParser::IsColumnName(const StringHelper& str)
{
    if (str.Contains("'"))
    {
        return false;
    }

    if (str.StartsWith("`") && str.EndsWith("`"))
    {
        return true;
    }

    if (!str.IsDouble() && !str.ContainsOnlyNumbers() && str.ContainsOnlyLettersNumbersAndUnderscore() && !str.StartsWithNumber())
    {
        return true;
    }

    return false;
}
