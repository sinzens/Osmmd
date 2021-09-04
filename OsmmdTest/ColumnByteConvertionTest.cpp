/*
* Created by Zeng Yinuo, 2021.09.04
*/

#include "ColumnByteConvertionTest.h"
#include "GlobalVariables.h"

#include "MockDataGenerator.h"

void Osmmd::ColumnByteConvertionTest::Test()
{
    constexpr int REPEAT = 10000;

    Column column = MockDataGenerator::MockColumn();

    Timer timer;
    timer.Start();

    for (int i = 0; i < REPEAT; i++)
    {
        Column::FromBytes(column.ToBytes());
    }

    timer.End();

    Column fromData = Column::FromBytes(column.ToBytes());

    std::lock_guard<std::mutex> guard(GlobalVariables::DEBUG_OUTPUT_MUTEX);

    Debug::WriteLine("-------------------------------------------------------------");
    Debug::WriteLine("Column byte convertion test:");
    Debug::WriteLine("Repeat {} times, costs {}ms", REPEAT, timer.Duration(TimeAccuracy::Millisecond));

    Debug::WriteLine("Original: {}", column);
    Debug::WriteLine("Parsed: {}", fromData);
    Debug::WriteLine("-------------------------------------------------------------");
}
