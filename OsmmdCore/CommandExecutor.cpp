/*
* Created by Zeng Yinuo, 2021.09.07
*/

#include "CommandExecutor.h"

void Osmmd::CommandExecutor::Execute()
{
    if (m_commands.size() == 0)
    {
        return;
    }

    for (std::shared_ptr<AtomicCommand> command : m_commands)
    {
        std::shared_ptr<CommandResult> result = command->Execute();

        if (!result->Successful)
        {
            std::cerr << result->ToString() << std::endl;
            break;
        }

        std::cout << result->ToString() << std::endl;
    }

    m_commands.clear();
}

void Osmmd::CommandExecutor::AddCommand(std::shared_ptr<AtomicCommand> command)
{
    m_commands.emplace_back(command);
}
