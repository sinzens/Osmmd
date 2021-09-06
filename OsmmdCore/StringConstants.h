/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
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
        } Error;
    };
}
