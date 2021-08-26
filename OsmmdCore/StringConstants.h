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
            static constexpr const char* NAME = "NAME";
            static constexpr const char* PATH = "PATH";
        } DriverConfiguration;

        static const struct
        {
            static constexpr const char* TIMING = "TIMING";
        } PerformanceConfiguration;
    };
}
