/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "Condition.h"

namespace Osmmd
{
    struct OSMMD_CORE_API SelectCommandArg
    {
        std::string Table;
        std::vector<Condition> Conditions;

        std::vector<std::string> ColumnNames;

        SelectCommandArg
        (
            const std::string& table,
            const std::vector<Condition>& conditions,
            const std::vector<std::string>& columnNames
        );

        SelectCommandArg& operator=(const SelectCommandArg& other);
    };
}
