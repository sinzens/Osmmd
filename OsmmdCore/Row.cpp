/*
* Created by Zeng Yinuo, 2021.09.01
* Edited by Zeng Yinuo, 2021.09.04
*/

#include "Row.h"

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
    //int dataLength = Value(Bytes(bytes.begin(), bytes.begin() + sizeof(int32_t))).ToInteger();
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
        row.Columns.emplace_back(Column::FromBytes(columnData));

        columnDataBeginIndex += columnDataLength;
    }

    return row;
}
