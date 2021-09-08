/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "DataType.h"
#include "DateTime.h"

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

        Value(int32_t value);
        Value(const char* str);
        Value(const std::string& str);
        Value(double value);
        Value(const DateTime& dateTime);

        bool IsEmpty() const;
        int GetLength() const;

        int32_t ToInteger() const noexcept;
        std::string ToChar() const noexcept;
        double ToDouble() const noexcept;
        DateTime ToDateTime() const noexcept;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        int Compare(const Value& other) const override;

        Value DeepCopy() const;

        DataType GetType() const;
        const Bytes& GetBytes() const;

        static Value FromInteger(int32_t value);
        static Value FromChar(const char* str);
        static Value FromChar(const std::string& str);
        static Value FromDouble(double value);
        static Value FromDateTime(const DateTime& dateTime);

        static int32_t GetLengthFromBytesHead(const Bytes& bytes);

        Value& operator=(const Value& other);

    private:
        DataType m_type;

        std::shared_ptr<Bytes> m_bytes;
    };
}
