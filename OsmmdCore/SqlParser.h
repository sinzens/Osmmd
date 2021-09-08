/*
* Created by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "SqlParseResult.h"
#include "StringHelper.h"
#include "DataType.h"
#include "ColumnValue.h"
#include "Condition.h"

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

        static SqlParseResult ParseUseDatabaseCommand(const StringHelper& sql);

        static SqlParseResult ParseInsertCommand(const StringHelper& sql);
        static SqlParseResult ParseDeleteCommand(const StringHelper& sql);
        static SqlParseResult ParseUpdateCommand(const StringHelper& sql);
        static SqlParseResult ParseSelectCommand(const StringHelper& sql);

        static SqlParseResult NoSuchCommandResult(const StringHelper& command);
        static SqlParseResult UnknownIndexStrategyResult(const StringHelper& indexStrategy);
        static SqlParseResult UnknownTypeResult(const StringHelper& type);
        static SqlParseResult ColumnNotExistResult(const StringHelper& columnName, const StringHelper& tableName);

        static std::string CheckIdentifierValid(const StringHelper& identifier);

        static std::vector<std::string> SplitCreateTableDeclarations(const std::string& declaration);
        static std::vector<std::string> SplitConditions(const std::string& conditions);
        static std::vector<std::string> SplitUpdateValues(const std::string& values);

        static DataType ParseType(const StringHelper& str);
        static std::shared_ptr<ColumnValue> ParseValue(const StringHelper& str);

        static std::vector<Condition> ParseConditions(const StringHelper& str, std::string& error);
        static Condition ParseCondition(const StringHelper& str, std::string& error);

        static bool IsColumnName(const StringHelper& str);
    };
}
