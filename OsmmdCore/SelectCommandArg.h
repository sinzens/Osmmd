/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "DataTable.h"
#include "Condition.h"

namespace Osmmd
{
    struct OSMMD_CORE_API SelectCommandArg
    {
        std::shared_ptr<DataTable> Table;
        std::vector<Condition> Conditions;

        SelectCommandArg(std::shared_ptr<DataTable> table, const std::vector<Condition>& conditions);

        SelectCommandArg& operator=(const SelectCommandArg& other);
    };
}
