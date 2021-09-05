/*
* Created by Zeng Yinuo, 2021.09.01
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#include "ColumnValue.h"

Osmmd::ColumnValue::ColumnValue()
{
}

Osmmd::ColumnValue::ColumnValue(const ColumnValue& other)
    : Data(other.Data)
{
}

Osmmd::ColumnValue::ColumnValue(const Value& value)
    : Data(value)
{
}

int Osmmd::ColumnValue::GetLength() const
{
    return this->Data.GetLength();
}

std::string Osmmd::ColumnValue::ToString() const
{
    return this->Data.ToString();
}

Bytes Osmmd::ColumnValue::ToBytes() const
{
    return this->Data.ToBytes();
}

int Osmmd::ColumnValue::Compare(const ColumnValue& other) const
{
    return this->Data.Compare(other.Data);
}

Osmmd::ColumnValue Osmmd::ColumnValue::FromBytes(DataType type, const Bytes& bytes)
{
    return ColumnValue(Value(type, bytes));
}

std::shared_ptr<Osmmd::ColumnValue> Osmmd::ColumnValue::PtrFromBytes(DataType type, const Bytes& bytes)
{
    return std::make_shared<ColumnValue>(Value(type, bytes));
}

Osmmd::ColumnValue& Osmmd::ColumnValue::operator=(const ColumnValue& other)
{
    this->Data = other.Data;

    return *this;
}
