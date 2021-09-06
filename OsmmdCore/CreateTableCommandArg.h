/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "DataTableConfiguration.h"
#include "Row.h"

namespace Osmmd
{
    struct OSMMD_CORE_API CreateTableCommandArg
    {
        DataTableConfiguration Config;
        Row RowDefinition;

        CreateTableCommandArg(const DataTableConfiguration& config, const Row& rowDefinition);

        CreateTableCommandArg& operator=(const CreateTableCommandArg& other);
    };
}
