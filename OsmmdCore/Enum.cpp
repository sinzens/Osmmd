/*
* Created by Zeng Yinuo, 2021.09.04
*/

#include "Enum.h"

std::string Osmmd::GetDataTypeName(DataType type)
{
    switch (type)
    {
    case DataType::Integer:
        return "int";
    case DataType::Char:
        return "char";
    }
}
