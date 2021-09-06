/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "AtomicCommand.h"
#include "UpdateCommandArg.h"

namespace Osmmd
{
    class OSMMD_CORE_API UpdateCommand : public AtomicCommand
    {
    public:
        UpdateCommand(const UpdateCommandArg& arg);

    protected:
        std::shared_ptr<CommandResult> DoExecute() override;

    private:
        UpdateCommandArg m_arg;
    };
}
