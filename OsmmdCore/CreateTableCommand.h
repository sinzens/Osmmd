/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "AtomicCommand.h"
#include "CreateTableCommandArg.h"

namespace Osmmd
{
    class OSMMD_CORE_API CreateTableCommand : public AtomicCommand
    {
    public:
        CreateTableCommand(const CreateTableCommandArg& arg);

    protected:
        std::shared_ptr<CommandResult> DoExecute() override;

    private:
        CreateTableCommandArg m_arg;
    };
}
