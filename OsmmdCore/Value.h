/*
* Created by Zeng Yinuo, 2021.09.04
*/

#pragma once

#include "ISerializable.h"
#include "DataType.h"

namespace Osmmd
{
    class OSMMD_CORE_API Value : public ISerializable
    {
    public:
        Value();
        Value(const Value& other);
        Value(DataType type, const Bytes& bytes);

        bool IsEmpty() const;

        int32_t ToInteger() const noexcept;
        std::string ToChar() const noexcept;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        const Bytes& Data() const;

        static Value FromInteger(int32_t value);
        static Value FromChar(const char* str);
        static Value FromChar(const std::string& str);

    private:
        DataType m_type;

        Bytes m_bytes;
    };
}
