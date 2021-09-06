/*
* Created by Zeng Yinuo, 2021.09.06
*/

#include "Condition.h"

Osmmd::Condition::Condition()
    : Operator(ConditionOperator::Equal)
    , Value(nullptr)
{
}

Osmmd::Condition::Condition(const Condition& other)
    : Operator(other.Operator)
    , ColumnIndexes(other.ColumnIndexes)
    , Value(other.Value)
{
}

Osmmd::Condition::Condition
(
    ConditionOperator opt,
    const std::vector<int>& indexes,
    std::shared_ptr<ColumnValue> value
)
    : Operator(opt)
    , ColumnIndexes(indexes)
    , Value(value)
{
}

bool Osmmd::Condition::IsColumnInvolved(int index) const
{
    return std::find(this->ColumnIndexes.begin(), this->ColumnIndexes.end(), index) != this->ColumnIndexes.end();
}

bool Osmmd::Condition::IsSimpleEqualCondition() const
{
    return this->ColumnIndexes.size() == 1 && this->Operator == ConditionOperator::Equal;
}

Osmmd::Condition& Osmmd::Condition::operator=(const Condition& other)
{
    this->Operator = other.Operator;
    this->ColumnIndexes = other.ColumnIndexes;
    this->Value = other.Value;

    return *this;
}
