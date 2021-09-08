/*
* Created by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "CommandExecutor.h"

std::vector<std::shared_ptr<Osmmd::CommandResult>> Osmmd::CommandExecutor::Execute()
{
    if (m_commands.size() == 0)
    {
        return {};
    }

    std::vector<std::shared_ptr<Osmmd::CommandResult>> results;

    for (std::shared_ptr<AtomicCommand> command : m_commands)
    {
        std::shared_ptr<CommandResult> result = command->Execute();
        results.emplace_back(result);

        if (!result->Successful)
        {
            break;
        }
    }

    m_commands.clear();

    return results;
}

void Osmmd::CommandExecutor::AddCommand(std::shared_ptr<AtomicCommand> command)
{
    m_commands.emplace_back(command);
}

void Osmmd::CommandExecutor::ClearCommands()
{
    m_commands.clear();
}
