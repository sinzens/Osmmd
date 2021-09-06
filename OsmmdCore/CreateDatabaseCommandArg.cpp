/*
* Created by Zeng Yinuo, 2021.09.06
*/

#include "CreateDatabaseCommandArg.h"

Osmmd::CreateDatabaseCommandArg::CreateDatabaseCommandArg(const std::string& name)
    : Name(name)
{
}

Osmmd::CreateDatabaseCommandArg& Osmmd::CreateDatabaseCommandArg::operator=(const CreateDatabaseCommandArg& other)
{
    this->Name = other.Name;

    return *this;
}
