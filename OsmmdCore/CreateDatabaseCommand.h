/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "AtomicCommand.h"
#include "CreateDatabaseCommandArg.h"

namespace Osmmd
{
    class OSMMD_CORE_API CreateDatabaseCommand : public AtomicCommand
    {
    public:
        CreateDatabaseCommand(const CreateDatabaseCommandArg& arg);

    protected:
        std::shared_ptr<CommandResult> DoExecute() override;

    private:
        CreateDatabaseCommandArg m_arg;
    };
}
