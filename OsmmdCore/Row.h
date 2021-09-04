/*
* Created by Zeng Yinuo, 2021.09.01
* Edited by Zeng Yinuo, 2021.09.04
*/

#pragma once

#include "Column.h"

namespace Osmmd
{
    struct OSMMD_CORE_API Row : public ISerializable
    {
        std::vector<Column> Columns;

        std::string ToString() const override;
        Bytes ToBytes() const override;
    };
}
