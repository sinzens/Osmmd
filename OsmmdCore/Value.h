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
        Value(DataType type, const std::vector<unsigned char>& bytes);

        bool IsEmpty() const;

        int32_t ToInteger() const noexcept;
        std::string ToChar() const noexcept;

        std::string ToBytes() const override;

        static Value FromInteger(int32_t value);
        static Value FromChar(const char* str);
        static Value FromChar(const std::string& str);

    private:
        DataType m_type;

        std::vector<unsigned char> m_bytes;
    };
}
