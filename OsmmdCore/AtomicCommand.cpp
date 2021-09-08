/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "AtomicCommand.h"
#include "StringConstants.h"

#include "Driver.h"
#include "Timer.h"

std::shared_ptr<Osmmd::CommandResult> Osmmd::AtomicCommand::Execute()
{
    if (TIMING_ON)
    {
        Timer timer;
        timer.Start();

        std::shared_ptr<CommandResult> result = this->DoExecute();

        timer.End();
        result->TimeElapse = timer.Duration(TimeAccuracy::Millisecond);

        return result;
    }
    
    return this->DoExecute();
}

Osmmd::CommandType Osmmd::AtomicCommand::GetType() const
{
    return m_type;
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::AtomicCommand::NoCurrentDatabaseResult() const
{
    return std::make_shared<CommandResult>
    (
        m_type,
        0,
        0,
        false,
        StringConstants::Error.COMMAND_NO_CURRENT_DATABASE,
        0
    );
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::AtomicCommand::NoSuchDatabaseResult(const std::string& databaseName) const
{
    char buffer[50]{};
    sprintf_s(buffer, "%s '%s'", StringConstants::Error.COMMAND_NO_SUCH_DATABASE, databaseName.c_str());

    return std::make_shared<CommandResult>(m_type, 0, 0, false, buffer, 0);
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::AtomicCommand::NoSuchTableResult(const std::string& tableName) const
{
    char buffer[50]{};
    sprintf_s(buffer, "%s '%s'", StringConstants::Error.COMMAND_NO_SUCH_TABLE, tableName.c_str());

    return std::make_shared<CommandResult>(m_type, 0, 0, false, buffer, 0);
}
