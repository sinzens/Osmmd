/*
* Created by Zeng Yinuo, 2021.09.01
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
*/

#include "Column.h"
#include "Enum.h"
#include "Value.h"
#include "DataType.h"

Osmmd::Column::Column()
    : Length(0)
    , Type(DataType::Char)
{
}

Osmmd::Column::Column(const Column& other)
    : Name(other.Name)
    , Length(other.Length)
    , Type(other.Type)
{
}

Osmmd::Column::Column(const std::string& name, int length, DataType type)
    : Name(name)
    , Length(length)
    , Type(type)
{
}

std::string Osmmd::Column::ToString() const
{
    char buffer[100]{};

    sprintf_s
    (
        buffer,
        "(Name: %s, Length: %d, Type: %s)",
        this->Name.c_str(),
        this->Length,
        GetDataTypeName(this->Type).c_str()
    );

    return buffer;
}

Bytes Osmmd::Column::ToBytes() const
{
    int32_t dataLength = (3 * sizeof(int32_t)) + this->Name.length() + sizeof(DataType);

    Value dataLengthData = Value::FromInteger(dataLength);
    Value nameLengthData = Value::FromInteger(this->Name.length());
    Value lengthData = Value::FromInteger(this->Length);

    Bytes bytes(dataLength, 0);

    auto dataLengthBegin = bytes.begin();
    auto nameLengthBegin = dataLengthBegin + sizeof(int32_t);
    auto nameBegin = nameLengthBegin + sizeof(int32_t);
    auto lengthBegin = nameBegin + this->Name.length();
    auto typeBegin = lengthBegin + sizeof(int32_t);

    std::copy(dataLengthData.GetBytes().begin(), dataLengthData.GetBytes().end(), dataLengthBegin);
    std::copy(nameLengthData.GetBytes().begin(), nameLengthData.GetBytes().end(), nameLengthBegin);

    std::copy(this->Name.begin(), this->Name.end(), nameBegin);
    std::copy(lengthData.GetBytes().begin(), lengthData.GetBytes().end(), lengthBegin);
    
    bytes.at(typeBegin - bytes.begin()) = static_cast<unsigned char>(this->Type);

    return bytes;
}

Osmmd::Column Osmmd::Column::FromBytes(const Bytes& bytes)
{
    auto nameLengthBegin = bytes.begin() + sizeof(int32_t);
    auto nameBegin = nameLengthBegin + sizeof(int32_t);

    int32_t nameLength = Value(DataType::Integer, std::make_shared<Bytes>(nameLengthBegin, nameBegin)).ToInteger();

    auto lengthBegin = nameBegin + nameLength;
    auto typeBegin = lengthBegin + sizeof(int32_t);

    Bytes nameData(nameBegin, lengthBegin);

    std::string name(nameData.begin(), nameData.end());
    int32_t length = Value(DataType::Integer, std::make_shared<Bytes>(lengthBegin, typeBegin)).ToInteger();
    DataType type = static_cast<DataType>(bytes.at(typeBegin - bytes.begin()));

    return Column(name, length, type);
}

Osmmd::Column& Osmmd::Column::operator=(const Column& other)
{
    this->Name = other.Name;
    this->Length = other.Length;
    this->Type = other.Type;

    return *this;
}

bool Osmmd::Column::operator==(const Column& other) const
{
    return this->Name == other.Name && this->Length == other.Length && this->Type == other.Type;
}

bool Osmmd::Column::operator!=(const Column& other) const
{
    return !(this->Name == other.Name && this->Length == other.Length && this->Type == other.Type);
}
