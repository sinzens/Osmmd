/*
* Created by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "AtomicCommand.h"

namespace Osmmd
{
    class OSMMD_CORE_API CommandExecutor
    {
    public:
        std::vector<std::shared_ptr<CommandResult>> Execute();

        void AddCommand(std::shared_ptr<AtomicCommand> command);
        void ClearCommands();

    private:
        std::deque<std::shared_ptr<AtomicCommand>> m_commands;
    };
}
