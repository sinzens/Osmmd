/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "SelectCommandArg.h"

Osmmd::SelectCommandArg::SelectCommandArg
(
    const std::string& table,
    const std::vector<Condition>& conditions,
    const std::vector<std::string>& columnNames
)
    : Table(table)
    , Conditions(conditions)
    , ColumnNames(columnNames)
{
}

Osmmd::SelectCommandArg& Osmmd::SelectCommandArg::operator=(const SelectCommandArg& other)
{
    this->Table = other.Table;
    this->Conditions = other.Conditions;
    this->ColumnNames = other.ColumnNames;

    return *this;
}
