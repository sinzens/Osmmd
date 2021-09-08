/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "Condition.h"
#include "Enum.h"

Osmmd::Condition::Condition()
    : Operator(ConditionOperator::Equal)
    , Value(nullptr)
{
}

Osmmd::Condition::Condition(const Condition& other)
    : Operator(other.Operator)
    , ColumnIndexes(other.ColumnIndexes)
    , ColumnNames(other.ColumnNames)
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

Osmmd::Condition::Condition
(
    ConditionOperator opt,
    const std::vector<std::string>& names,
    std::shared_ptr<ColumnValue> value
)
    : Operator(opt)
    , ColumnNames(names)
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
    this->ColumnNames = other.ColumnNames;
    this->Value = other.Value;

    return *this;
}

std::string Osmmd::Condition::ToString() const
{
    char buffer[300]{};
    sprintf_s(buffer, "(Operator: %s, ColumnNames: ", GetConditionOperatorName(this->Operator).c_str());

    std::string str = buffer;
    str.append("[");

    for (int i = 0; i < this->ColumnNames.size(); i++)
    {
        str.append(this->ColumnNames.at(i));
        
        if (i != this->ColumnNames.size() - 1)
        {
            str.append(", ");
        }
    }

    str.append("], ColumnIndexes: [");

    for (int i = 0; i < this->ColumnIndexes.size(); i++)
    {
        str.append(Value::FromInteger(this->ColumnIndexes.at(i)).ToString());

        if (i != this->ColumnIndexes.size() - 1)
        {
            str.append(", ");
        }
    }

    str.append("], Value: [");

    if (this->Value)
    {
        str.append(this->Value->ToString());
    }

    str.append("])");

    return str;
}

Bytes Osmmd::Condition::ToBytes() const
{
    return Bytes();
}
