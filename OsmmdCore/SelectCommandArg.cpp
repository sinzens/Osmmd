/*
* Created by Zeng Yinuo, 2021.09.06
*/

#include "SelectCommandArg.h"

Osmmd::SelectCommandArg::SelectCommandArg
(
    std::shared_ptr<DataTable> table,
    const std::vector<Condition>& conditions,
    const Row& selectRow
)
    : Table(table)
    , Conditions(conditions)
{
}

Osmmd::SelectCommandArg& Osmmd::SelectCommandArg::operator=(const SelectCommandArg& other)
{
    this->Table = other.Table;
    this->Conditions = other.Conditions;
    this->SelectRow = other.SelectRow;

    return *this;
}
