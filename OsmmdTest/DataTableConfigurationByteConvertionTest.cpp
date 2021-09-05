/*
* Created by Zeng Yinuo, 2021.09.05
*/

#include "DataTableConfigurationByteConvertionTest.h"
#include "GlobalVariables.h"

#include "MockDataGenerator.h"

void Osmmd::DataTableConfigurationByteConvertionTest::Test()
{
    constexpr int REPEAT = 10000;

    DataTableConfiguration config = MockDataGenerator::MockDataTableConfiguration();

    Timer timer;
    timer.Start();

    for (int i = 0; i < REPEAT; i++)
    {
        DataTableConfiguration::FromBytes(config.ToBytes());
    }

    timer.End();

    DataTableConfiguration fromData = DataTableConfiguration::FromBytes(config.ToBytes());

    std::lock_guard<std::mutex> guard(GlobalVariables::DEBUG_OUTPUT_MUTEX);

    Debug::WriteLine("-------------------------------------------------------------");
    Debug::WriteLine("DataTableConfiguration byte convertion test:");
    Debug::WriteLine("Repeat {} times, costs {}ms", REPEAT, timer.Duration(TimeAccuracy::Millisecond));

    Debug::WriteLine("Original: {}", config);
    Debug::WriteLine("Parsed: {}", fromData);
    Debug::WriteLine("-------------------------------------------------------------");
}
