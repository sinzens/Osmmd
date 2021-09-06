/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "AtomicCommand.h"
#include "SelectCommandArg.h"

namespace Osmmd
{
    class OSMMD_CORE_API SelectCommand : public AtomicCommand
    {
    public:
        SelectCommand(const SelectCommandArg& arg);

    protected:
        std::shared_ptr<CommandResult> DoExecute() override;

    private:
        SelectCommandArg m_arg;
    };
}
