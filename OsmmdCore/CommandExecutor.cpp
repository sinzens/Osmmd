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
        /*std::future<std::shared_ptr<CommandResult>> futureResult = std::async
        ([&command]() -> std::shared_ptr<CommandResult>
            {
                return command->Execute();
            }
        );

        std::shared_ptr<CommandResult> result = futureResult.get();*/

        std::shared_ptr<CommandResult> result = command->Execute();
        std::cout << result->ToString() << std::endl;

        if (!result->Successful)
        {
            break;
        }
    }

    m_commands.clear();
}

void Osmmd::CommandExecutor::AddCommand(std::shared_ptr<AtomicCommand> command)
{
    m_commands.emplace_back(command);
}
