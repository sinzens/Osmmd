/*
* Created by Zeng Yinuo, 2021.09.04
*/

#include "Enum.h"
#include "Value.h"
#include "StringConstants.h"

Osmmd::Value::Value()
    : m_type(DataType::Char)
{
}

Osmmd::Value::Value(const Value& other)
    : m_type(other.m_type)
    , m_bytes(other.m_bytes)
{
}

Osmmd::Value::Value(const Bytes& bytes)
    : m_type(DataType::Char)
    , m_bytes(bytes)
{
}

Osmmd::Value::Value(DataType type, const Bytes& bytes)
    : m_type(type)
    , m_bytes(bytes)
{
}

bool Osmmd::Value::IsEmpty() const
{
    return m_bytes.size() == 0;
}

int Osmmd::Value::GetLength() const
{
    switch (m_type)
    {
    case DataType::Integer:
        return sizeof(int32_t);
    case DataType::Char:
        return this->ToChar().size();
    }

    return 0;
}

int32_t Osmmd::Value::ToInteger() const noexcept
{
    assert(m_type == DataType::Integer, StringConstants::Error.VALUE_NOT_INTEGER);

    int32_t number = m_bytes.at(0) & 0xFF;

    number |= ((m_bytes.at(1) << 8) & 0xFF00);
    number |= ((m_bytes.at(2) << 16) & 0xFF0000);
    number |= ((m_bytes.at(3) << 24) & 0xFF000000);

    return number;
}

std::string Osmmd::Value::ToChar() const noexcept
{
    assert(m_type == DataType::Char, StringConstants::Error.VALUE_NOT_CHAR);

    return std::string(m_bytes.begin(), m_bytes.end());
}

std::string Osmmd::Value::ToString() const
{
    switch (m_type)
    {
    case DataType::Integer:
    {
        char buffer[255]{};
        sprintf_s(buffer, "%d", this->ToInteger());
        return buffer;
    }
    case DataType::Char:
        return this->ToChar();
        break;
    }

    return GetDataTypeName(m_type);
}

Bytes Osmmd::Value::ToBytes() const
{
    return m_bytes;
}

int Osmmd::Value::Compare(const Value& other) const
{
    switch (m_type)
    {
    case DataType::Integer: {
        int32_t a = this->ToInteger();
        int32_t b = other.ToInteger();

        return a > b ? 1 : (a < b ? -1 : 0);
    }
    case DataType::Char:
        return this->ToChar().compare(other.ToChar());
    }

    return 0;
}

Osmmd::DataType Osmmd::Value::GetType() const
{
    return m_type;
}

const Bytes& Osmmd::Value::GetBytes() const
{
    return m_bytes;
}

Osmmd::Value Osmmd::Value::FromInteger(int32_t value)
{
    unsigned char data[sizeof(int32_t)]{};

    data[0] = value;
    data[1] = value >> 8;
    data[2] = value >> 16;
    data[3] = value >> 24;

    Value result;

    result.m_type = DataType::Integer;
    result.m_bytes = std::vector<unsigned char>(data, data + sizeof(int32_t));

    return result;
}

Osmmd::Value Osmmd::Value::FromChar(const char* str)
{
    std::string data = str;

    Value result;

    result.m_type = DataType::Char;
    result.m_bytes = std::vector<unsigned char>(data.c_str(), data.c_str() + data.size());

    return result;
}

Osmmd::Value Osmmd::Value::FromChar(const std::string& str)
{
    Value result;

    result.m_type = DataType::Char;
    result.m_bytes = std::vector<unsigned char>(str.c_str(), str.c_str() + str.size());

    return result;
}
