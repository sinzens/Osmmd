/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    struct OSMMD_CORE_API CreateDatabaseCommandArg
    {
        std::string Name;

        CreateDatabaseCommandArg(const std::string& name);

        CreateDatabaseCommandArg& operator=(const CreateDatabaseCommandArg& other);
    };
}
