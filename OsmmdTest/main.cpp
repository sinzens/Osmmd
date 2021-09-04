/*
* Created by Zeng Yinuo, 2021.09.04
*/

#include "../OsmmdCore/Debug.h"
#include "../OsmmdCore/Timer.h"

#include "../OsmmdCore/Column.h"

using namespace Osmmd;

void ColumnByteConvertionTest();

int main()
{
    ColumnByteConvertionTest();
}

void ColumnByteConvertionTest()
{
    Column column;

    column.Name = "TestColumn";
    column.Length = 4;
    column.Type = DataType::Integer;

    Bytes bytes = column.ToBytes();

    constexpr int REPEAT = 10000;

    Timer::Start();

    for (int i = 0; i < REPEAT; i++)
    {
        Column::FromBytes(bytes);
    }

    Timer::End();

    Column fromData = Column::FromBytes(bytes);

    Debug::WriteLine("Column byte convertion test:");
    Debug::WriteLine("Repeat {} times, costs {}ms", REPEAT, Timer::Duration(TimeAccuracy::Millisecond));

    Debug::WriteLine("Original: {}", column);
    Debug::WriteLine("Parsed: {}", fromData);
}
