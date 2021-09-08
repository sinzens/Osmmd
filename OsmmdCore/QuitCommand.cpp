/*
* Created by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "QuitCommand.h"

Osmmd::QuitCommand::QuitCommand()
{
    m_type = CommandType::Quit;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::QuitCommand::DoExecute()
{
    return std::make_shared<CommandResult>(CommandType::Quit, 0, 0, true, std::string(), 0);
}
