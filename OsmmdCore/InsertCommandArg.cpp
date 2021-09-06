/*
* Created by Zeng Yinuo, 2021.09.06
*/

#include "InsertCommandArg.h"

Osmmd::InsertCommandArg::InsertCommandArg(std::shared_ptr<DataTable> table, std::shared_ptr<RowValue> value)
    : Table(table)
    , Value(value)
{
}

Osmmd::InsertCommandArg& Osmmd::InsertCommandArg::operator=(const InsertCommandArg& other)
{
    this->Table = other.Table;
    this->Value = other.Value;

    return *this;
}
