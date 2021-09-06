/*
* Created by Zeng Yinuo, 2021.09.06
*/

#include "SelectCommand.h"
#include "SelectCommandResult.h"

Osmmd::SelectCommand::SelectCommand(const SelectCommandArg& arg)
    : m_arg(arg)
{
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::SelectCommand::DoExecute()
{
    std::shared_ptr<SelectIndexResult> indexResult = m_arg.Table->Select(m_arg.Conditions, m_arg.SelectRow);

    return std::make_shared<SelectCommandResult>
    (
        CommandType::Select,
        indexResult->AffectRowCount,
        indexResult->AffectColCount,
        true,
        std::string(),
        0,
        indexResult->Results
    );
}
