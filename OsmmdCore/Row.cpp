/*
* Created by Zeng Yinuo, 2021.09.01
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.06
*/

#include "Row.h"

void Osmmd::Row::AddColumn(const Column& column)
{
    this->Columns.emplace_back(column);
    this->m_nameIndexMap.insert({ column.Name, this->Columns.size() - 1 });
}

void Osmmd::Row::RemoveColumn(int index)
{
    if (index < 0 || index >= this->Columns.size())
    {
        return;
    }

    this->m_nameIndexMap.erase(this->Columns.at(index).Name);
    this->Columns.erase(this->Columns.begin() + index);
}

void Osmmd::Row::RemoveColumn(const std::string& name)
{
    auto target = this->m_nameIndexMap.find(name);

    if (target == this->m_nameIndexMap.end())
    {
        return;
    }

    this->Columns.erase(this->Columns.begin() + target->second);
    this->m_nameIndexMap.erase(target);
}

void Osmmd::Row::UpdateColumn(int index, const Column& column)
{
    if (index < 0 || index >= this->Columns.size())
    {
        return;
    }

    this->m_nameIndexMap.erase(this->Columns.at(index).Name);
    this->m_nameIndexMap.insert({ column.Name, index });

    this->Columns.at(index) = column;
}

void Osmmd::Row::UpdateColumn(const std::string& name, const Column& column)
{
    auto target = this->m_nameIndexMap.find(name);

    if (target == this->m_nameIndexMap.end())
    {
        return;
    }

    this->Columns.at(target->second) = column;
    this->m_nameIndexMap.at(name) = target->second;
}

const Osmmd::Column& Osmmd::Row::ColumnAt(int index) const
{
    return this->Columns.at(index);
}

const Osmmd::Column& Osmmd::Row::ColumnAt(const std::string& name) const
{
    return this->Columns.at(this->m_nameIndexMap.at(name));
}

bool Osmmd::Row::HasColumn(const std::string& name) const
{
    return this->m_nameIndexMap.find(name) != this->m_nameIndexMap.end();
}

bool Osmmd::Row::HasColumn(const Column& column) const
{
    if (this->m_nameIndexMap.find(column.Name) == this->m_nameIndexMap.end())
    {
        return false;
    }

    for (const Column& col : this->Columns)
    {
        if (col == column)
        {
            return true;
        }
    }

    return false;
}

int Osmmd::Row::ColumnIndex(const std::string& name) const
{
    auto target = m_nameIndexMap.find(name);

    if (target == m_nameIndexMap.end())
    {
        return -1;
    }

    return target->second;
}

int Osmmd::Row::ColumnIndex(const Column& column) const
{
    for (auto i = this->Columns.begin(); i != this->Columns.end(); i++)
    {
        if ((*i) == column)
        {
            return i - this->Columns.begin();
        }
    }

    return -1;
}

std::string Osmmd::Row::ToString() const
{
    std::string result;

    char headerBuffer[50]{};
    sprintf_s(headerBuffer, "Row: (Column count: %lld)\n", this->Columns.size());

    result.append(headerBuffer);

    for (int i = 0; i < this->Columns.size(); i++)
    {
        char buffer[150]{};
        sprintf_s(buffer, "\tColumn %d: %s\n", i + 1, this->Columns.at(i).ToString().c_str());

        result.append(buffer);
    }

    return result;
}

Bytes Osmmd::Row::ToBytes() const
{
    int dataLength = 2 * sizeof(int32_t);
    int columnCount = this->Columns.size();

    Bytes columnsData;

    for (const Column& col : this->Columns)
    {
        Bytes columnData = col.ToBytes();
        columnsData.insert(columnsData.end(), columnData.begin(), columnData.end());
        dataLength += columnData.size();
    }

    const char* dataLengthDataPtr = reinterpret_cast<const char*>(&dataLength);
    const char* columnCountDataPtr = reinterpret_cast<const char*>(&columnCount);

    Bytes dataLengthData(dataLengthDataPtr, dataLengthDataPtr + sizeof(int32_t));
    Bytes columnCountData(columnCountDataPtr, columnCountDataPtr + sizeof(int32_t));

    Bytes bytes(dataLength, 0);

    std::copy(dataLengthData.begin(), dataLengthData.end(), bytes.begin());
    std::copy(columnCountData.begin(), columnCountData.end(), bytes.begin() + sizeof(int32_t));
    std::copy(columnsData.begin(), columnsData.end(), bytes.begin() + (2 * sizeof(int32_t)));

    return bytes;
}

Osmmd::Row Osmmd::Row::FromBytes(const Bytes& bytes)
{
    auto dataLengthBegin = bytes.begin();
    auto columnCountBegin = dataLengthBegin + sizeof(int32_t);
    auto columnsDataBegin = columnCountBegin + sizeof(int32_t);

    int columnCount = Value(DataType::Integer, Bytes(columnCountBegin, columnsDataBegin)).ToInteger();

    Row row;

    int columnDataBeginIndex = columnsDataBegin - bytes.begin();
    for (int i = 0; i < columnCount; i++)
    {
        auto columnDataBegin = bytes.begin() + columnDataBeginIndex;
        int columnDataLength = Value(DataType::Integer, Bytes(columnDataBegin, columnDataBegin + sizeof(int32_t))).ToInteger();

        Bytes columnData(columnDataBegin, columnDataBegin + columnDataLength);
        Column column = Column::FromBytes(columnData);

        row.AddColumn(column);

        columnDataBeginIndex += columnDataLength;
    }

    return row;
}

bool Osmmd::Row::operator==(const Row& other) const
{
    if (this->Columns.size() != other.Columns.size())
    {
        return false;
    }

    for (int i = 0; i < this->Columns.size(); i++)
    {
        if (this->Columns.at(i) != other.Columns.at(i))
        {
            return false;
        }
    }

    return true;
}

bool Osmmd::Row::operator!=(const Row& other) const
{
    if (this->Columns.size() != other.Columns.size())
    {
        return true;
    }

    for (int i = 0; i < this->Columns.size(); i++)
    {
        if (this->Columns.at(i) != other.Columns.at(i))
        {
            return true;
        }
    }

    return false;
}
