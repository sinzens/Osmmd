/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "SelectCommand.h"
#include "SelectCommandResult.h"
#include "StringConstants.h"
#include "Driver.h"

Osmmd::SelectCommand::SelectCommand(const SelectCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::Select;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::SelectCommand::DoExecute()
{
    std::shared_ptr<Database> database = Driver::GetInstance().GetCurrentDatabase();

    if (!database)
    {
        return this->NoCurrentDatabaseResult();
    }

    std::shared_ptr<DataTable> table = Driver::GetInstance().GetCurrentDatabase()->GetTable(m_arg.Table);

    if (!table)
    {
        return this->NoSuchTableResult(m_arg.Table);
    }

    Row selectRow;

    std::shared_ptr<SelectIndexResult> indexResult = table->Select(m_arg.Conditions, selectRow);

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
