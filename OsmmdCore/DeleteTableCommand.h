/*
* Created by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "AtomicCommand.h"
#include "DeleteTableCommandArg.h"

namespace Osmmd
{
    class OSMMD_CORE_API DeleteTableCommand : public AtomicCommand
    {
    public:
        DeleteTableCommand(const DeleteTableCommandArg& arg);

    protected:
        std::shared_ptr<CommandResult> DoExecute() override;

    private:
        DeleteTableCommandArg m_arg;
    };
}
