/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
* Edited by Zeng Yinuo, 2021.09.09
*/

#include "InsertCommand.h"
#include "StringConstants.h"
#include "Driver.h"

Osmmd::InsertCommand::InsertCommand(const InsertCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::Insert;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::InsertCommand::DoExecute()
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

    if (m_arg.Value->Values.size() != table->GetRowDefinition().Columns.size())
    {
        return std::make_shared<CommandResult>
        (
            CommandType::Insert,
            0,
            0,
            false,
            StringConstants::Error.SQL_COLUMNS_NOT_MATCH,
            0
        );
    }

    for (int i = 0; i < m_arg.Value->Values.size(); i++)
    {
        std::shared_ptr<ColumnValue> value = m_arg.Value->Values.at(i);

        Column tempColumn("unnamed", value->GetLength(), value->GetType());
        Column column = table->GetRowDefinition().ColumnAt(i);

        if (tempColumn.Length != column.Length || tempColumn.Type != column.Type)
        {
            if
            (
                (tempColumn.Type == DataType::Integer && column.Type == DataType::Double) ||
                (tempColumn.Type == DataType::Double && column.Type == DataType::Integer)
            )
            {
                if (tempColumn.Type == DataType::Integer && column.Type == DataType::Double)
                {
                    std::shared_ptr<ColumnValue> value = m_arg.Value->Values.at(i);
                    value->Data = Value::FromDouble(static_cast<double>(value->Data.ToInteger()));
                }
                else
                {
                    std::shared_ptr<ColumnValue> value = m_arg.Value->Values.at(i);
                    value->Data = Value::FromInteger(static_cast<int32_t>(value->Data.ToDouble()));
                }
            }
            else
            {
                return this->NoSuchColumnResult(tempColumn.ToString(), m_arg.Table);
            }
        }
    }

    std::shared_ptr<Osmmd::IndexResult> indexResult = table->Insert(m_arg.Value);

    if (!indexResult->IsSuccessful())
    {
        return std::make_shared<CommandResult>(CommandType::Insert, 0, 0, false, indexResult->Message, 0);
    }

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
