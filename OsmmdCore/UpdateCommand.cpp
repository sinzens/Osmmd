/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "UpdateCommand.h"
#include "StringConstants.h"
#include "Driver.h"

Osmmd::UpdateCommand::UpdateCommand(const UpdateCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::Update;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::UpdateCommand::DoExecute()
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

    for (const Column& column : m_arg.UpdateRow.Columns)
    {
        if (!table->GetRowDefinition().HasColumn(column))
        {
            return this->NoSuchColumnResult(column.Name, m_arg.Table);
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

    std::shared_ptr<IndexResult> indexResult = table->Update(m_arg.Conditions, m_arg.UpdateRow, m_arg.UpdateValue);

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
