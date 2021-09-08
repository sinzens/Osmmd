/*
* Created by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    struct OSMMD_CORE_API UseDatabaseCommandArg
    {
        std::string Name;

        UseDatabaseCommandArg(const std::string& name);

        UseDatabaseCommandArg& operator=(const UseDatabaseCommandArg& other);
    };
}
