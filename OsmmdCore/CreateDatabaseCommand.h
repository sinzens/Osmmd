/*
* Created by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "AtomicCommand.h"
#include "Database.h"

namespace Osmmd
{
    class OSMMD_CORE_API CreateDatabaseCommand : public AtomicCommand
    {
    public:
        CreateDatabaseCommand(const Database& database);

        CommandResult Execute() override;

    private:
        Database m_database;
    };
}
