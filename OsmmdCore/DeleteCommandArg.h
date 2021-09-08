/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "DataTable.h"
#include "Condition.h"

namespace Osmmd
{
    struct OSMMD_CORE_API DeleteCommandArg
    {
        std::string Table;
        std::vector<Condition> Conditions;

        DeleteCommandArg(const std::string& table, const std::vector<Condition>& conditions);

        DeleteCommandArg& operator=(const DeleteCommandArg& other);
    };
}
