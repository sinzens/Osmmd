/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "AtomicCommand.h"
#include "DeleteCommandArg.h"

namespace Osmmd
{
    class OSMMD_CORE_API DeleteCommand : public AtomicCommand
    {
    public:
        DeleteCommand(const DeleteCommandArg& arg);

    protected:
        std::shared_ptr<CommandResult> DoExecute() override;

    private:
        DeleteCommandArg m_arg; 
    };
}
