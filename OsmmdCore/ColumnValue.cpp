/*
* Created by Zeng Yinuo, 2021.09.01
* Edited by Zeng Yinuo, 2021.09.04
*/

#include "ColumnValue.h"

std::string Osmmd::ColumnValue::ToString() const
{
    return this->Value.ToString();
}

Bytes Osmmd::ColumnValue::ToBytes() const
{
    return this->Value.ToBytes();
}
