/*
* Created by Zeng Yinuo, 2021.09.04
*/

#include "ColumnValueByteConvertionTest.h"
#include "GlobalVariables.h"

#include "MockDataGenerator.h"

void Osmmd::ColumnValueByteConvertionTest::Test()
{
    constexpr int REPEAT = 10000;

    ColumnValue value = MockDataGenerator::MockColumnValue();

    Timer timer;
    timer.Start();

    for (int i = 0; i < REPEAT; i++)
    {
        ColumnValue::FromBytes(DataType::Integer, value.ToBytes());
    }

    timer.End();

    ColumnValue fromData = ColumnValue::FromBytes(value.Data.GetType(), value.ToBytes());

    std::lock_guard<std::mutex> guard(GlobalVariables::DEBUG_OUTPUT_MUTEX);

    Debug::WriteLine("-------------------------------------------------------------");
    Debug::WriteLine("ColumnValue byte convertion test:");
    Debug::WriteLine("Repeat {} times, costs {}ms", REPEAT, timer.Duration(TimeAccuracy::Millisecond));

    Debug::WriteLine("Original: {}", value);
    Debug::WriteLine("Parsed: {}", fromData);
    Debug::WriteLine("-------------------------------------------------------------");
}
