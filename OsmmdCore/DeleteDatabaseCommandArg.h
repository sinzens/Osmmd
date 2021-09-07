/*
* Created by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    struct OSMMD_CORE_API DeleteDatabaseCommandArg
    {
        std::string Name;

        DeleteDatabaseCommandArg(const std::string& name);

        DeleteDatabaseCommandArg& operator=(const DeleteDatabaseCommandArg& other);
    };
}
