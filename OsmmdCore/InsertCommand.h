/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "AtomicCommand.h"
#include "InsertCommandArg.h"

namespace Osmmd
{
    class OSMMD_CORE_API InsertCommand : public AtomicCommand
    {
    public:
        InsertCommand(const InsertCommandArg& arg);

    protected:
        std::shared_ptr<CommandResult> DoExecute() override;

    private:
        InsertCommandArg m_arg;
    };
}
