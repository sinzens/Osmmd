/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "DeleteCommand.h"
#include "StringConstants.h"
#include "Driver.h"

Osmmd::DeleteCommand::DeleteCommand(const DeleteCommandArg& arg)
    : m_arg(arg)
{
    m_type = CommandType::Delete;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::DeleteCommand::DoExecute()
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

    for (Condition& condition : m_arg.Conditions)
    {
        bool fetched = condition.FetchColumnIndexes(table->GetRowDefinition());

        if (!fetched)
        {
            return this->CannotFetchConditionResult(condition, table->GetRowDefinition());
        }
    }

    std::shared_ptr<Osmmd::IndexResult> indexResult = table->Delete(m_arg.Conditions);

    if (!indexResult->IsSuccessful())
    {
        return std::make_shared<CommandResult>(CommandType::Delete, 0, 0, false, indexResult->Message, 0);
    }
    
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
