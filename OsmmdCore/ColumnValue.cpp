/*
* Created by Zeng Yinuo, 2021.09.01
* Edited by Zeng Yinuo, 2021.09.04
*/

#include "ColumnValue.h"

std::string Osmmd::ColumnValue::ToString() const
{
    return this->Data.ToString();
}

Bytes Osmmd::ColumnValue::ToBytes() const
{
    return this->Data.ToBytes();
}

Osmmd::ColumnValue Osmmd::ColumnValue::FromBytes(DataType type, const Bytes& bytes)
{
    ColumnValue value;
    value.Data = Value(type, bytes);
    return value;
}
