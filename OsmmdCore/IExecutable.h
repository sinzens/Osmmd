/*
* Created by Zeng Yinuo, 2021.08.23
*/

#pragma once

#include "CommandResult.h"

namespace Osmmd
{
    class OSMMD_CORE_API IExecutable
    {
    public:
        virtual CommandResult Execute() = 0;
    };
}
