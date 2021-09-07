/*
* Created by Zeng Yinuo, 2021.09.07
*/

#include "QuitCommand.h"

Osmmd::QuitCommand::QuitCommand()
{
    m_type = CommandType::Quit;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::QuitCommand::DoExecute()
{
    return std::shared_ptr<CommandResult>();
}
