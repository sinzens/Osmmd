/*
* Created by Zeng Yinuo, 2021.09.01
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#pragma once

#include "Value.h"

namespace Osmmd
{
    struct OSMMD_CORE_API ColumnValue : public ISerializable, public IComparable<ColumnValue>
    {
        Value Data;

        ColumnValue();
        ColumnValue(const ColumnValue& other);
        ColumnValue(const Value& value);

        int GetLength() const;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        int Compare(const ColumnValue& other) const override;

        static ColumnValue FromBytes(DataType type, const Bytes& bytes);
        static std::shared_ptr<ColumnValue> PtrFromBytes(DataType type, const Bytes& bytes);

        ColumnValue& operator=(const ColumnValue& other);
    };
}
