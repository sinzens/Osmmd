/*
* Created by Zeng Yinuo, 2021.09.06
*/

#include "CreateTableCommandArg.h"

Osmmd::CreateTableCommandArg::CreateTableCommandArg(const DataTableConfiguration& config, const Row& rowDefinition)
    : Config(config)
    , RowDefinition(rowDefinition)
{
}

Osmmd::CreateTableCommandArg& Osmmd::CreateTableCommandArg::operator=(const CreateTableCommandArg& other)
{
    this->Config = other.Config;
    this->RowDefinition = other.RowDefinition;

    return *this;
}
