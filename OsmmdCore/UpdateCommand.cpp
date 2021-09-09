/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
* Edited by Zeng Yinuo, 2021.09.09
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

    for (int i = 0; i < m_arg.UpdateRow.Columns.size(); i++)
    {
        Column& column = m_arg.UpdateRow.Columns.at(i);

        if (!table->GetRowDefinition().HasColumn(column.Name))
        {
            return this->NoSuchColumnResult(column.Name, m_arg.Table);
        }

        Column columnDefinition = table->GetRowDefinition().ColumnAt(column.Name);

        if (column != columnDefinition)
        {
            if
            (
                (column.Type == DataType::Integer && columnDefinition.Type == DataType::Double) ||
                (column.Type == DataType::Double && columnDefinition.Type == DataType::Integer)
            )
            {
                if (column.Type == DataType::Integer && columnDefinition.Type == DataType::Double)
                {
                    column.Type = DataType::Double;
                    column.Length = sizeof(double);

                    std::shared_ptr<ColumnValue> value = m_arg.UpdateValue->Values.at(i);
                    value->Data = Value::FromDouble(static_cast<double>(value->Data.ToInteger()));
                }
                else
                {
                    column.Type = DataType::Integer;
                    column.Length = sizeof(int32_t);

                    std::shared_ptr<ColumnValue> value = m_arg.UpdateValue->Values.at(i);
                    value->Data = Value::FromInteger(static_cast<int32_t>(value->Data.ToDouble()));
                }
            }
            else
            {
                return this->NoSuchColumnResult(column.ToString(), m_arg.Table);
            }
        }

        /*if (!table->GetRowDefinition().HasColumn(column))
        {
            return this->NoSuchColumnResult(column.ToString(), m_arg.Table);
        }*/

        if (table->IsIndex(column.Name) || table->IsPrimaryKey(column.Name))
        {
            return this->CannotUpdateKeyResult(column.Name);
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
