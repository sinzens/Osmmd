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
    , Value(other.Value)
{
}

Osmmd::Condition::Condition(ConditionOperator opt, std::shared_ptr<ColumnValue> value)
    : Operator(opt)
    , Value(value)
{
}

Osmmd::Condition& Osmmd::Condition::operator=(const Condition& other)
{
    this->Operator = other.Operator;
    this->Value = other.Value;

    return *this;
}
