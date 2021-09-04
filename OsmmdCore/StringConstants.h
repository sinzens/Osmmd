/*
* Created by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    struct OSMMD_CORE_API StringConstants
    {
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