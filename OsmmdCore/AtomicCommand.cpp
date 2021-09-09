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

std::shared_ptr<Osmmd::CommandResult> Osmmd::AtomicCommand::NoSuchColumnResult
(
    const std::string& columnName,
    const std::string& tableName
) const
{
    char buffer[300]{};
    sprintf_s(buffer, "No such column '%s' in table '%s'", columnName.c_str(), tableName.c_str());

    return std::make_shared<CommandResult>(m_type, 0, 0, false, buffer, 0);
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::AtomicCommand::CannotFetchConditionResult
(
    const Condition& condition,
    const Row& rowDefinition
) const
{
    char buffer[1500]{};
    sprintf_s
    (
        buffer,
        "Cannot fetch condition: %s with row %s",
        condition.ToString().c_str(),
        rowDefinition.ToString().c_str()
    );

    return std::make_shared<CommandResult>(m_type, 0, 0, false, buffer, 0);
}

std::shared_ptr<Osmmd::CommandResult> Osmmd::AtomicCommand::CannotUpdateKeyResult(const std::string columnName)
{
    char buffer[100]{};
    sprintf_s(buffer, "Cannot update column '%s' because it's either primary key or index", columnName.c_str());

    return std::make_shared<CommandResult>(m_type, 0, 0, false, buffer, 0);
}
