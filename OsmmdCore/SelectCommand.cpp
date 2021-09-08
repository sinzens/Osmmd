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

    for (const std::string& column : m_arg.ColumnNames)
    {
        if (!table->GetRowDefinition().HasColumn(column) && column != "*")
        {
            return this->NoSuchColumnResult(column, m_arg.Table);
        }
    }

    for (Condition& condition : m_arg.Conditions)
    {
        bool fetched = condition.FetchColumnIndexes(table->GetRowDefinition());

        if (!fetched)
        {
            return this->CannotFetchConditionResult(condition, table->GetRowDefinition());
        }
    }

    Row selectRow = table->GetRowDefinition().Sliced(m_arg.ColumnNames);

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
