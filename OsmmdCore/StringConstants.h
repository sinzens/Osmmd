/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    struct OSMMD_CORE_API StringConstants
    {
        static const struct
        {
            static constexpr const char INTEGER[] = "int";
            static constexpr const char CHAR[] = "char";
            static constexpr const char UNKNOWN[] = "unknown";
        } DataType;

        static const struct
        {
            static constexpr const char BP_TREE[] = "BpTree";
            static constexpr const char HASH[] = "Hash";
            static constexpr const char UNKNOWN[] = "Unknown";
        } IndexStrategy;

        static const struct
        {
            static constexpr const char CREATE_DATABASE[] = "CREATE DATABASE";
            static constexpr const char CREATE_TABLE[] = "CREATE TABLE";
            static constexpr const char DELETE_DATABASE[] = "DELETE DATABASE";
            static constexpr const char DELETE_TABLE[] = "DELETE TABLE";
            static constexpr const char INSERT[] = "INSERT";
            static constexpr const char DELETE[] = "DELETE";
            static constexpr const char UPDATE[] = "UPDATE";
            static constexpr const char SELECT[] = "SELECT";
            static constexpr const char QUIT[] = "QUIT";
            static constexpr const char UNKNOWN[] = "UNKNOWN";
        } CommandType;

        static const struct
        {
            static constexpr const char CONFIG_FILE_NAME[] = "osmmd.config";
            static constexpr const char DRIVER_NAME[] = "Osmmd Driver";
        } Driver;

        static const struct
        {
            static constexpr const char NAME[] = "NAME";
            static constexpr const char PATH[] = "PATH";
            static constexpr const char DATABASES[] = "DATABASES";
        } DriverConfiguration;

        static const struct
        {
            static constexpr const char TIMING[] = "TIMING";
        } PerformanceConfiguration;

        static const struct
        {
            static constexpr const char VALUE_NOT_INTEGER[] = "Failed to convert non-integer value to integer.";
            static constexpr const char VALUE_NOT_CHAR[] = "Failed to convert non-char value to char.";

            static constexpr const char SQL_NO_SUCH_COMMAND[] = "No such command";
            static constexpr const char SQL_NO_DATABASE_NAME[] = "No database name given";
            static constexpr const char SQL_NO_DATATABLE_NAME[] = "No data table name given";
            static constexpr const char SQL_NO_DATATABLE_DEFINITION[] = "No data table definition given";
            static constexpr const char SQL_NO_DATATABLE_DEFINITION_END[] = "Data table definition should end with ')'";
            static constexpr const char SQL_NO_DATATABLE_DEFINITION_CONTENT[] = "Data table definition is empty";

            static constexpr const char SQL_INVALID_COLUMN_DEFINITION[] = "Invalid column definition";
            static constexpr const char SQL_INVALID_PRIMARY_KEY_DECLARATION[] = "Invalid primary key declaration";
            static constexpr const char SQL_INVALID_INDEX_DECLARATION[] = "Invalid index declaration";

            static constexpr const char SQL_INVALID_IDENTIFIER_NOT_ALLOWED_CHARACTER[]
                = "Invalid identifier, only letters, numbers and underscore are allowed";

            static constexpr const char SQL_INVALID_IDENTIFIER_STARTS_WITH_NUMBER[]
                = "Invalid identifier, an identifier cannot start with a number";

            static constexpr const char SQL_INVALID_IDENTIFIER_TOO_SHORT[]
                = "Invalid identifier, an identifier must be at least 2 letters long";

            static constexpr const char SQL_UNKNOWN_TYPE[] = "Unknown type";
            static constexpr const char SQL_CHAR_NO_LENGTH[] = "A length must be specified for type 'char'";
            static constexpr const char SQL_LENGTH_EMPTY[] = "A length cannot be empty";
            static constexpr const char SQL_NO_COLUMNS[] = "No columns specified for data table";
            static constexpr const char SQL_COLUMN_NOT_EXIST[] = "Column doesn't exist in data table";

        } Error;
    };
}
