/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
*/

#include "InsertCommand.h"

Osmmd::InsertCommand::InsertCommand(const InsertCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::Insert;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::InsertCommand::DoExecute()
{
    std::shared_ptr<Osmmd::IndexResult> indexResult = m_arg.Table->Insert(m_arg.Value);

    return std::make_shared<CommandResult>
    (
        CommandType::Insert,
        indexResult->AffectRowCount,
        indexResult->AffectColCount,
        true,
        std::string(),
        0
    );
}
