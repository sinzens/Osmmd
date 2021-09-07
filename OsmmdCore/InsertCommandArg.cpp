/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
*/

#include "InsertCommandArg.h"

Osmmd::InsertCommandArg::InsertCommandArg(const std::string& table, std::shared_ptr<RowValue> value)
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
