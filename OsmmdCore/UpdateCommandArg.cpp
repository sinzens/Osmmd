/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "UpdateCommandArg.h"

Osmmd::UpdateCommandArg::UpdateCommandArg
(
    const std::string& table,
    const std::vector<Condition>& conditions,
    const Row& updateRow,
    std::shared_ptr<RowValue> updateValue
)
    : Table(table)
    , Conditions(conditions)
    , UpdateRow(updateRow)
    , UpdateValue(updateValue)
{
}

Osmmd::UpdateCommandArg& Osmmd::UpdateCommandArg::operator=(const UpdateCommandArg& other)
{
    this->Table = other.Table;
    this->Conditions = other.Conditions;
    this->UpdateRow = other.UpdateRow;
    this->UpdateValue = other.UpdateValue;

    return *this;
}
