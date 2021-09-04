/*
* Created by Zeng Yinuo, 2021.09.01
* Edited by Zeng Yinuo, 2021.09.04
*/

#pragma once

#include "Value.h"

namespace Osmmd
{
    struct OSMMD_CORE_API ColumnValue : public ISerializable
    {
        Value Data;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static ColumnValue FromBytes(DataType type, const Bytes& bytes);
    };
}
