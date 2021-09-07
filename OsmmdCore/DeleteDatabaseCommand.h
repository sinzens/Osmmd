/*
* Created by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "AtomicCommand.h"
#include "DeleteDatabaseCommandArg.h"

namespace Osmmd
{
    class OSMMD_CORE_API DeleteDatabaseCommand : public AtomicCommand
    {
    public:
        DeleteDatabaseCommand(const DeleteDatabaseCommandArg& arg);

    protected:
        std::shared_ptr<CommandResult> DoExecute() override;

    private:
        DeleteDatabaseCommandArg m_arg;
    };
}
