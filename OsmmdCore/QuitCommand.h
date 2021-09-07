/*
* Created by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "AtomicCommand.h"
#include "CommandResult.h"

namespace Osmmd
{
    class OSMMD_CORE_API QuitCommand : public AtomicCommand
    {
    public:
        QuitCommand();

    protected:
        std::shared_ptr<CommandResult> DoExecute() override;
    };
}
