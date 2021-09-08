/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "RowValue.h"

Osmmd::RowValue::RowValue()
{
}

Osmmd::RowValue::RowValue(const RowValue& other)
    : Values(other.Values)
{
}

Osmmd::RowValue::RowValue(std::shared_ptr<RowValue> other)
    : Values(other->Values)
{
}

Osmmd::RowValue::RowValue(const std::vector<std::shared_ptr<ColumnValue>>& values)
    : Values(values)
{
}

int Osmmd::RowValue::GetLength() const
{
    int length = 0;

    for (auto i = this->Values.begin(); i != this->Values.end(); i++)
    {
        length += (*i)->GetLength();
    }

    return length;
}

Osmmd::RowValue Osmmd::RowValue::Sliced(const Row& newDefinition, const Row& oldDefinition, bool strict) const
{
    if (newDefinition.Columns.size() > oldDefinition.Columns.size())
    {
        return *this;
    }

    if (newDefinition == oldDefinition)
    {
        return *this;
    }

    RowValue result;

    for (const Column& col : newDefinition.Columns)
    {
        auto target = strict
            ? std::find(oldDefinition.Columns.begin(), oldDefinition.Columns.end(), col)
            : oldDefinition.Columns.begin() + oldDefinition.ColumnIndex(col);

        if (target != oldDefinition.Columns.end())
        {
            result.Values.emplace_back(this->Values.at(target - oldDefinition.Columns.begin()));
        }
    }

    return result;
}

bool Osmmd::RowValue::MeetConditions(const std::vector<Condition>& conditions) const
{
    if (conditions.size() == 0)
    {
        return true;
    }

    for (const Condition& condition : conditions)
    {
        if (!this->MeetCondition(condition))
        {
            return false;
        }
    }

    return true;
}

bool Osmmd::RowValue::MeetCondition(const Condition& condition) const
{
    switch (condition.ColumnIndexes.size())
    {
    case 0:
        return condition.Value->Data.ToInteger() != 0;
    case 1:
        return this->MeetUnaryColumnCondition(condition);
    case 2:
        return this->MeetBinaryColumnCondition(condition);
    }

    return false;
}

int Osmmd::RowValue::Update(const Row& updateRow, const Row& originalRow, std::shared_ptr<RowValue> updateValue)
{
    int counter = 0;

    if (updateRow.Columns.size() != updateValue->Values.size())
    {
        return counter;
    }

    for (int i = 0; i < updateRow.Columns.size(); i++)
    {
        int columnIndex = originalRow.ColumnIndex(updateRow.ColumnAt(i).Name);

        if (*(this->Values.at(columnIndex)) != *(updateValue->Values.at(i)))
        {
            this->Values.at(columnIndex) = updateValue->Values.at(i);
            counter++;
        }
    }

    return counter;
}

Osmmd::RowValue Osmmd::RowValue::DeepCopy() const
{
    std::vector<std::shared_ptr<ColumnValue>> values;

    for (std::shared_ptr<ColumnValue> value : values)
    {
        values.emplace_back(std::make_shared<ColumnValue>(value->Data.DeepCopy()));
    }

    return RowValue(values);
}

std::string Osmmd::RowValue::ToString() const
{
    std::string result = "(";

    for (auto i = this->Values.begin(); i != this->Values.end(); i++)
    {
        result.append((*i)->Data.ToString());
        result.append(i == this->Values.end() - 1 ? ")" : ", ");
    }

    return result;
}

Bytes Osmmd::RowValue::ToBytes() const
{
    Bytes bytes;

    for (std::shared_ptr<ColumnValue> value : this->Values)
    {
        bytes.insert(bytes.end(), value->Data.GetBytes().begin(), value->Data.GetBytes().end());
    }

    return bytes;
}

Osmmd::RowValue Osmmd::RowValue::FromBytes(const Row& rowDefinition, const Bytes& bytes)
{
    RowValue row;
    int columnDataBeginIndex = 0;

    for (auto i = rowDefinition.Columns.begin(); i != rowDefinition.Columns.end(); i++)
    {
        const Column& col = (*i);

        auto columnDataBegin = bytes.begin() + columnDataBeginIndex;
        auto columnDataEnd = columnDataBegin + col.Length;

        row.Values.emplace_back(ColumnValue::PtrFromBytes(col.Type, Bytes(columnDataBegin, columnDataEnd)));
        columnDataBeginIndex += col.Length;
    }

    return row;
}

Osmmd::RowValue& Osmmd::RowValue::operator=(const RowValue& other)
{
    this->Values = other.Values;

    return *this;
}

bool Osmmd::RowValue::operator==(const RowValue& other) const
{
    if (other.Values.size() != this->Values.size())
    {
        return false;
    }

    for (int i = 0; i < this->Values.size(); i++)
    {
        if (this->Values.at(i) != other.Values.at(i))
        {
            return false;
        }
    }

    return true;
}

bool Osmmd::RowValue::operator!=(const RowValue& other) const
{
    if (other.Values.size() != this->Values.size())
    {
        return true;
    }

    for (int i = 0; i < this->Values.size(); i++)
    {
        if (this->Values.at(i) != other.Values.at(i))
        {
            return true;
        }
    }

    return false;
}

bool Osmmd::RowValue::MeetUnaryColumnCondition(const Condition& condition) const
{
    switch (condition.Operator)
    {
    case ConditionOperator::Equal:
        return *(this->Values.at(condition.ColumnIndexes.front())) == *(condition.Value);
    case ConditionOperator::GreaterThan:
        return *(this->Values.at(condition.ColumnIndexes.front())) > *(condition.Value);
    case ConditionOperator::GreaterThanEqual:
        return *(this->Values.at(condition.ColumnIndexes.front())) >= *(condition.Value);
    case ConditionOperator::LessThan:
        return *(this->Values.at(condition.ColumnIndexes.front())) < *(condition.Value);
    case ConditionOperator::LessThanEqual:
        return *(this->Values.at(condition.ColumnIndexes.front())) <= *(condition.Value);
    case ConditionOperator::NotEqual:
        return *(this->Values.at(condition.ColumnIndexes.front())) != *(condition.Value);
    }

    return false;
}

bool Osmmd::RowValue::MeetBinaryColumnCondition(const Condition& condition) const
{
    switch (condition.Operator)
    {
    case ConditionOperator::Equal:
        return *(this->Values.at(condition.ColumnIndexes.front())) == *(this->Values.at(condition.ColumnIndexes.back()));
    case ConditionOperator::GreaterThan:
        return *(this->Values.at(condition.ColumnIndexes.front())) > *(this->Values.at(condition.ColumnIndexes.back()));
    case ConditionOperator::GreaterThanEqual:
        return *(this->Values.at(condition.ColumnIndexes.front())) >= *(this->Values.at(condition.ColumnIndexes.back()));
    case ConditionOperator::LessThan:
        return *(this->Values.at(condition.ColumnIndexes.front())) < *(this->Values.at(condition.ColumnIndexes.back()));
    case ConditionOperator::LessThanEqual:
        return *(this->Values.at(condition.ColumnIndexes.front())) <= *(this->Values.at(condition.ColumnIndexes.back()));
    case ConditionOperator::NotEqual:
        return *(this->Values.at(condition.ColumnIndexes.front())) != *(this->Values.at(condition.ColumnIndexes.back()));
    }

    return false;
}
