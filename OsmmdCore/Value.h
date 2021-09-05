/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#pragma once

#include "ISerializable.h"
#include "IComparable.h"
#include "DataType.h"

namespace Osmmd
{
    class OSMMD_CORE_API Value : public ISerializable, public IComparable<Value>
    {
    public:
        Value();
        Value(const Value& other);
        Value(const Bytes& bytes);
        Value(std::shared_ptr<Bytes> bytes);
        Value(DataType type, const Bytes& bytes);
        Value(DataType type, std::shared_ptr<Bytes> bytes);

        bool IsEmpty() const;
        int GetLength() const;

        int32_t ToInteger() const noexcept;
        std::string ToChar() const noexcept;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        int Compare(const Value& other) const override;

        DataType GetType() const;
        const Bytes& GetBytes() const;

        static Value FromInteger(int32_t value);
        static Value FromChar(const char* str);
        static Value FromChar(const std::string& str);

        Value& operator=(const Value& other);

    private:
        DataType m_type;

        std::shared_ptr<Bytes> m_bytes;
    };
}
