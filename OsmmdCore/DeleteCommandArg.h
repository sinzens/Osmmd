/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "DataTable.h"
#include "Condition.h"

namespace Osmmd
{
    struct OSMMD_CORE_API DeleteCommandArg
    {
        std::shared_ptr<DataTable> Table;
        std::vector<Condition> Conditions;

        DeleteCommandArg(std::shared_ptr<DataTable> table, const std::vector<Condition>& conditions);

        DeleteCommandArg& operator=(const DeleteCommandArg& other);
    };
}
