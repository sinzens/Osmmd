/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "ColumnValue.h"
#include "ConditionOperator.h"

namespace Osmmd
{
    struct OSMMD_CORE_API Condition : public ISerializable
    {
        ConditionOperator Operator;

        std::vector<int> ColumnIndexes;
        std::vector<std::string> ColumnNames;

        std::shared_ptr<ColumnValue> Value;

        Condition();
        Condition(const Condition& other);

        Condition
        (
            ConditionOperator opt,
            const std::vector<int>& indexes,
            std::shared_ptr<ColumnValue> value
        );

        Condition
        (
            ConditionOperator opt,
            const std::vector<std::string>& names,
            std::shared_ptr<ColumnValue> value
        );

        bool IsColumnInvolved(int index) const;

        bool IsSimpleEqualCondition() const;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        Condition& operator=(const Condition& other);
    };
}
