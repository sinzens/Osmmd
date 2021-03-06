/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "CommandResult.h"

namespace Osmmd
{
    class OSMMD_CORE_API IExecutable
    {
    public:
        virtual std::shared_ptr<CommandResult> Execute() = 0;
    };
}
