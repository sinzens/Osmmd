/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "DataTable.h"
#include "Condition.h"

namespace Osmmd
{
    struct OSMMD_CORE_API UpdateCommandArg
    {
        std::shared_ptr<DataTable> Table;
        std::vector<Condition> Conditions;

        Row UpdateRow;
        std::shared_ptr<RowValue> UpdateValue;

        UpdateCommandArg
        (
            std::shared_ptr<DataTable> table,
            const std::vector<Condition>& conditions,
            const Row& updateRow,
            std::shared_ptr<RowValue> updateValue
        );

        UpdateCommandArg& operator=(const UpdateCommandArg& other);
    };
}
