/*
* Created by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    struct OSMMD_CORE_API DeleteTableCommandArg
    {
        std::string Name;

        DeleteTableCommandArg(const std::string& name);

        DeleteTableCommandArg& operator=(const DeleteTableCommandArg& other);
    };
}
