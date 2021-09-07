/*
* Created by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "SqlParseResult.h"
#include "StringHelper.h"
#include "DataType.h"
#include "ColumnValue.h"

namespace Osmmd
{
    class OSMMD_CORE_API SqlParser
    {
    public:
        static SqlParseResult Parse(const std::string& sql);
        static SqlParseResult Parse(const StringHelper& sql);

    private:
        static SqlParseResult ParseQuitCommand(const StringHelper& sql);

        static SqlParseResult ParseCreateDatabaseCommand(const StringHelper& sql);
        static SqlParseResult ParseCreateTableCommand(const StringHelper& sql);

        static SqlParseResult ParseDeleteDatabaseCommand(const StringHelper& sql);
        static SqlParseResult ParseDeleteTableCommand(const StringHelper& sql);

        static SqlParseResult ParseInsertCommand(const StringHelper& sql);
        static SqlParseResult ParseDeleteCommand(const StringHelper& sql);
        static SqlParseResult ParseUpdateCommand(const StringHelper& sql);
        static SqlParseResult ParseSelectCommand(const StringHelper& sql);

        static SqlParseResult NoSuchCommandResult(const StringHelper& command);
        static SqlParseResult UnknownIndexStrategyResult(const StringHelper& indexStrategy);
        static SqlParseResult UnknownTypeResult(const StringHelper& type);
        static SqlParseResult ColumnNotExistResult(const StringHelper& columnName, const StringHelper& tableName);

        static std::string CheckIdentifierValid(const StringHelper& identifier);

        static std::vector<std::string> SplitCreateTableDeclarations(const std::string declaration);

        static DataType ParseType(const StringHelper& str);
        static std::shared_ptr<ColumnValue> ParseValue(const StringHelper& str);
    };
}
