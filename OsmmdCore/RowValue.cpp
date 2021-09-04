/*
* Created by Zeng Yinuo, 2021.09.04
*/

#include "RowValue.h"

std::string Osmmd::RowValue::ToString() const
{
    std::string result = "(";

    for (auto i = this->Values.begin(); i != this->Values.end(); i++)
    {
        result.append((*i).Data.ToString());
        result.append(i == this->Values.end() - 1 ? ")" : ", ");
    }

    return result;
}

Bytes Osmmd::RowValue::ToBytes() const
{
    Bytes bytes;

    for (const ColumnValue& value : this->Values)
    {
        bytes.insert(bytes.end(), value.Data.GetBytes().begin(), value.Data.GetBytes().end());
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

        row.Values.emplace_back(ColumnValue::FromBytes(col.Type, Bytes(columnDataBegin, columnDataEnd)));
        columnDataBeginIndex += col.Length;
    }

    return row;
}
