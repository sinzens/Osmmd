/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "DataTable.h"
#include "Condition.h"

namespace Osmmd
{
    struct OSMMD_CORE_API UpdateCommandArg
    {
        std::string Table;
        std::vector<Condition> Conditions;

        Row UpdateRow;
        std::shared_ptr<RowValue> UpdateValue;

        UpdateCommandArg
        (
            const std::string& table,
            const std::vector<Condition>& conditions,
            const Row& updateRow,
            std::shared_ptr<RowValue> updateValue
        );

        UpdateCommandArg& operator=(const UpdateCommandArg& other);
    };
}
