/*
* Created by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "AtomicCommand.h"
#include "UseDatabaseCommandArg.h"

namespace Osmmd
{
    class OSMMD_CORE_API UseDatabaseCommand : public AtomicCommand
    {
    public:
        UseDatabaseCommand(const UseDatabaseCommandArg& arg);

    protected:
        std::shared_ptr<CommandResult> DoExecute() override;

    private:
        UseDatabaseCommandArg m_arg;
    };
}
