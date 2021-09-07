/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
*/

#include "DeleteCommand.h"

Osmmd::DeleteCommand::DeleteCommand(const DeleteCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::Delete;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::DeleteCommand::DoExecute()
{
    std::shared_ptr<IndexResult> indexResult = m_arg.Table->Delete(m_arg.Conditions);
    
    return std::make_shared<CommandResult>
    (
        CommandType::Delete,
        indexResult->AffectRowCount,
        indexResult->AffectColCount,
        true,
        std::string(),
        0
    );
}
