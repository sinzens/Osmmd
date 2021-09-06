/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "ColumnValue.h"
#include "ConditionOperator.h"

namespace Osmmd
{
    struct OSMMD_CORE_API Condition
    {
        ConditionOperator Operator;
        std::shared_ptr<ColumnValue> Value;

        Condition();
        Condition(const Condition& other);
        Condition(ConditionOperator opt, std::shared_ptr<ColumnValue> value);

        Condition& operator=(const Condition& other);
    };
}
