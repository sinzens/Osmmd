/*
* Created by Zeng Yinuo, 2021.09.08
*/

#include "UseDatabaseCommandArg.h"

Osmmd::UseDatabaseCommandArg::UseDatabaseCommandArg(const std::string& name)
    : Name(name)
{
}

Osmmd::UseDatabaseCommandArg& Osmmd::UseDatabaseCommandArg::operator=(const UseDatabaseCommandArg& other)
{
    this->Name = other.Name;

    return *this;
}
