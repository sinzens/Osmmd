/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "IExecutable.h"
#include "Condition.h"
#include "Row.h"

namespace Osmmd
{
    class OSMMD_CORE_API AtomicCommand : public IExecutable
    {
    public:
        virtual std::shared_ptr<CommandResult> Execute() override;

        CommandType GetType() const;

    protected:
        virtual std::shared_ptr<CommandResult> DoExecute() = 0;

        std::shared_ptr<CommandResult> NoCurrentDatabaseResult() const;
        std::shared_ptr<CommandResult> NoSuchDatabaseResult(const std::string& databaseName) const;
        std::shared_ptr<CommandResult> NoSuchTableResult(const std::string& tableName) const;

        std::shared_ptr<CommandResult> NoSuchColumnResult
        (
            const std::string& columnName,
            const std::string& tableName
        ) const;

        std::shared_ptr<CommandResult> CannotFetchConditionResult
        (
            const Condition& condition,
            const Row& rowDefinition
        ) const;

        std::shared_ptr<CommandResult> CannotUpdateKeyResult(const std::string columnName);

        CommandType m_type = CommandType::Select;
    };
}


