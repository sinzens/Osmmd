/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
*/

#include "UpdateCommand.h"

Osmmd::UpdateCommand::UpdateCommand(const UpdateCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::Update;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::UpdateCommand::DoExecute()
{
    std::shared_ptr<IndexResult> indexResult = m_arg.Table->Update(m_arg.Conditions, m_arg.UpdateRow, m_arg.UpdateValue);

    return std::make_shared<CommandResult>
    (
        CommandType::Update,
        indexResult->AffectRowCount,
        indexResult->AffectColCount,
        true,
        std::string(),
        0
    );
}
