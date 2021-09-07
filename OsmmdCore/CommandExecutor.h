/*
* Created by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "AtomicCommand.h"

namespace Osmmd
{
    class OSMMD_CORE_API CommandExecutor
    {
    public:
        void Execute();

        void AddCommand(std::shared_ptr<AtomicCommand> command);

    private:
        std::deque<std::shared_ptr<AtomicCommand>> m_commands;
    };
}
