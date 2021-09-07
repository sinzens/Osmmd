/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "DataTable.h"

namespace Osmmd
{
    struct OSMMD_CORE_API InsertCommandArg
    {
        std::string Table;
        std::shared_ptr<RowValue> Value;

        InsertCommandArg(const std::string& table, std::shared_ptr<RowValue> value);

        InsertCommandArg& operator=(const InsertCommandArg& other);
    };
}
