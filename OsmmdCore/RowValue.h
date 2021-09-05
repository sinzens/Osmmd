/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#pragma once

#include "Row.h"
#include "ColumnValue.h"

namespace Osmmd
{
    struct OSMMD_CORE_API RowValue : public ISerializable
    {
        std::vector<std::shared_ptr<ColumnValue>> Values;

        int GetLength() const;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static RowValue FromBytes(const Row& rowDefinition, const Bytes& bytes);
    };
}
