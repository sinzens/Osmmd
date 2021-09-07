/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
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
        return std::make_shared<CommandResult>
        (
            CommandType::Insert,
            0,
            0,
            false,
            StringConstants::Error.COMMAND_NO_CURRENT_DATABASE,
            0
        );
    }

    std::shared_ptr<DataTable> table = Driver::GetInstance().GetCurrentDatabase()->GetTable(m_arg.Table);

    if (!table)
    {
        char buffer[50]{};
        sprintf_s(buffer, "%s '%s'", StringConstants::Error.COMMAND_NO_SUCH_TABLE, m_arg.Table.c_str());

        return std::make_shared<CommandResult>(CommandType::Insert, 0, 0, false, buffer, 0);
    }

    std::shared_ptr<Osmmd::IndexResult> indexResult = table->Insert(m_arg.Value);

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
