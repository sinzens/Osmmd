/*
* Created by Zeng Yinuo, 2021.09.04
*/

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

Osmmd::Value::Value(DataType type, const std::vector<unsigned char>& bytes)
    : m_type(type)
    , m_bytes(bytes)
{
}

bool Osmmd::Value::IsEmpty() const
{
    return m_bytes.size() == 0;
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

std::string Osmmd::Value::ToBytes() const
{
    return std::string();
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
    result.m_bytes = std::vector<unsigned char>
    (
        reinterpret_cast<const unsigned char*>(data.c_str()),
        reinterpret_cast<const unsigned char*>(data.c_str()) + data.size()
    );

    return result;
}

Osmmd::Value Osmmd::Value::FromChar(const std::string& str)
{
    Value result;

    result.m_type = DataType::Char;
    result.m_bytes = std::vector<unsigned char>
    (
        reinterpret_cast<const unsigned char*>(str.c_str()),
        reinterpret_cast<const unsigned char*>(str.c_str()) + str.size()
    );

    return result;
}
