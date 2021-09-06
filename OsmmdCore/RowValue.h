/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "Row.h"
#include "ColumnValue.h"
#include "Condition.h"

namespace Osmmd
{
    struct OSMMD_CORE_API RowValue : public ISerializable
    {
        std::vector<std::shared_ptr<ColumnValue>> Values;

        RowValue();
        RowValue(const RowValue& other);
        RowValue(std::shared_ptr<RowValue> other);
        RowValue(const std::vector<std::shared_ptr<ColumnValue>>& values);

        int GetLength() const;

        RowValue Sliced(const Row& newDefinition, const Row& oldDefinition, bool strict = true) const;

        bool MeetConditions(const std::vector<Condition>& conditions) const;
        bool MeetCondition(const Condition& condition) const;

        int Update(const Row& updateRow, const Row& originalRow, std::shared_ptr<RowValue> updateValue);

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static RowValue FromBytes(const Row& rowDefinition, const Bytes& bytes);

        RowValue& operator=(const RowValue& other);

        bool operator==(const RowValue& other) const;
        bool operator!=(const RowValue& other) const;

    private:
        bool MeetUnaryColumnCondition(const Condition& condition) const;
        bool MeetBinaryColumnCondition(const Condition& condition) const;
    };
}
