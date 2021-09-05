/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#include "RowValueByteConvertionTest.h"
#include "GlobalVariables.h"

#include "MockDataGenerator.h"

void Osmmd::RowValueByteConvertionTest::Test()
{
    constexpr int REPEAT = 10000;

    Row row = MockDataGenerator::MockRow(5);
    RowValue value = MockDataGenerator::MockRowValue(row);

    Timer timer;
    timer.Start();

    for (int i = 0; i < REPEAT; i++)
    {
        RowValue::FromBytes(row, value.ToBytes());
    }

    timer.End();

    RowValue fromData = RowValue::FromBytes(row, value.ToBytes());

    std::lock_guard<std::mutex> guard(GlobalVariables::DEBUG_OUTPUT_MUTEX);

    Debug::WriteLine("-------------------------------------------------------------");
    Debug::WriteLine("RowValue byte convertion test:");
    Debug::WriteLine("Repeat {} times, costs {}ms", REPEAT, timer.Duration(TimeAccuracy::Millisecond));

    Debug::WriteLine("Original: {}", value);
    Debug::WriteLine("Parsed: {}", fromData);
    Debug::WriteLine("-------------------------------------------------------------");
}
