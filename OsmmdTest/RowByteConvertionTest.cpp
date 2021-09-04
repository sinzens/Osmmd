/*
* Created by Zeng Yinuo, 2021.09.04
*/

#include "RowByteConvertionTest.h"
#include "GlobalVariables.h"

#include "MockDataGenerator.h"

void Osmmd::RowByteConvertionTest::Test()
{
    constexpr int REPEAT = 10000;
    constexpr int COLUMN = 5;

    Row row = MockDataGenerator::MockRow();

    Timer timer;
    timer.Start();

    for (int i = 0; i < REPEAT; i++)
    {
        Row::FromBytes(row.ToBytes());
    }

    timer.End();

    Row fromData = Row::FromBytes(row.ToBytes());

    std::lock_guard<std::mutex> guard(GlobalVariables::DEBUG_OUTPUT_MUTEX);

    Debug::WriteLine("-------------------------------------------------------------");
    Debug::WriteLine("Row byte convertion test:");
    Debug::WriteLine("Repeat {} times, costs {}ms", REPEAT, timer.Duration(TimeAccuracy::Millisecond));

    Debug::WriteLine("Original:\n{}", row);
    Debug::WriteLine("Parsed:\n{}", fromData);
    Debug::WriteLine("-------------------------------------------------------------");
}
