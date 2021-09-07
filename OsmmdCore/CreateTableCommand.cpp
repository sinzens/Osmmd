/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
*/

#include "CreateTableCommand.h"

Osmmd::CreateTableCommand::CreateTableCommand(const CreateTableCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::CreateTable;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::CreateTableCommand::DoExecute()
{
    return std::shared_ptr<CommandResult>();
}
