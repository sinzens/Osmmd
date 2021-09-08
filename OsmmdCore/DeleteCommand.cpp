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

    std::shared_ptr<Osmmd::IndexResult> indexResult = table->Delete(m_arg.Conditions);
    
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
