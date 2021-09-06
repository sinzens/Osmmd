/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "DataTable.h"

namespace Osmmd
{
    struct OSMMD_CORE_API InsertCommandArg
    {
        std::shared_ptr<DataTable> Table;
        std::shared_ptr<RowValue> Value;

        InsertCommandArg(std::shared_ptr<DataTable> table, std::shared_ptr<RowValue> value);

        InsertCommandArg& operator=(const InsertCommandArg& other);
    };
}
