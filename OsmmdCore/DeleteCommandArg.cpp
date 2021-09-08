/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "DeleteCommandArg.h"

Osmmd::DeleteCommandArg::DeleteCommandArg(const std::string& table, const std::vector<Condition>& conditions)
    : Table(table)
    , Conditions(conditions)
{
}

Osmmd::DeleteCommandArg& Osmmd::DeleteCommandArg::operator=(const DeleteCommandArg& other)
{
    this->Table = other.Table;
    this->Conditions = other.Conditions;

    return *this;
}
