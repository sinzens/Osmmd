/*
* Created by Zeng Yinuo, 2021.09.07
*/

#include "SqlParser.h"
#include "StringConstants.h"

#include "CreateDatabaseCommand.h"
#include "CreateTableCommand.h"
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

    if (lowercased.StartsWith("q"))
    {
        return ParseQuitCommand(lowercased);
    }

    if (lowercased.StartsWith("create database "))
    {
        return ParseCreateDatabaseCommand(simplified);
    }

    if (lowercased.StartsWith("create table "))
    {
        return ParseCreateTableCommand(simplified);
    }

    if (lowercased.StartsWith("drop database "))
    {
        return ParseDeleteDatabaseCommand(simplified);
    }

    if (lowercased.StartsWith("drop table "))
    {
        return ParseDeleteTableCommand(simplified);
    }

    if (lowercased.StartsWith("insert into "))
    {
        return ParseInsertCommand(simplified);
    }

    if (lowercased.StartsWith("delete from "))
    {
        return ParseDeleteCommand(simplified);
    }

    if (lowercased.StartsWith("select "))
    {
        return ParseSelectCommand(simplified);
    }

    if (lowercased.StartsWith("update "))
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

    size_t definitionEnd = afterCommand.GetString().find_last_of(")", definitionBegin);

    if (definitionEnd == std::string::npos)
    {
        return SqlParseResult(false, StringConstants::Error.SQL_NO_DATATABLE_DEFINITION_END);
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
    std::vector<std::string> declarations = definitionContent.Split(",");

    if (declarations.size() == 0)
    {
        declarations.emplace_back(definitionContent.GetString());
    }

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
            length = Value(DataType::Integer, Bytes(lengthContent.GetString().begin(), lengthContent.GetString().end())).ToInteger();
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

    return SqlParseResult(true, std::make_shared<CreateTableCommand>(CreateTableCommandArg(config, rowDefinition)));
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseDeleteDatabaseCommand(const StringHelper& sql)
{
    return SqlParseResult();
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseDeleteTableCommand(const StringHelper& sql)
{
    return SqlParseResult();
}

Osmmd::SqlParseResult Osmmd::SqlParser::ParseInsertCommand(const StringHelper& sql)
{
    return SqlParseResult();
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

Osmmd::SqlParseResult Osmmd::SqlParser::UnknownTypeResult(const StringHelper& type)
{
    char buffer[100]{};
    sprintf_s(buffer, "%s '%s'", StringConstants::Error.SQL_UNKNOWN_TYPE, type.GetString().c_str());

    return SqlParseResult(false, buffer);
}

Osmmd::SqlParseResult Osmmd::SqlParser::ColumnNotExistResult(const StringHelper& columnName, const StringHelper& tableName)
{
    return SqlParseResult();
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
