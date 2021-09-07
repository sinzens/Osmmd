/*
* Created by Zeng Yinuo, 2021.09.07
*/

#include "DeleteTableCommandArg.h"

Osmmd::DeleteTableCommandArg::DeleteTableCommandArg(const std::string& name)
    : Name(name)
{
}

Osmmd::DeleteTableCommandArg& Osmmd::DeleteTableCommandArg::operator=(const DeleteTableCommandArg& other)
{
    this->Name = other.Name;

    return *this;
}
