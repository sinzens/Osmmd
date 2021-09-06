/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
*/

#include "HashIndexerTest.h"
#include "GlobalVariables.h"

#include "MockDataGenerator.h"

void Osmmd::HashIndexerTest::Test()
{
    constexpr int ROW_COUNT = 10000;

    Row rowDefinition = MockDataGenerator::MockRow();
    HashIndexer indexer = MockDataGenerator::MockHashIndexer(ROW_COUNT, rowDefinition);

    Timer timer;
    timer.Start();

    auto result = indexer.Select({ MockDataGenerator::MockCondition(rowDefinition) }, rowDefinition, rowDefinition);

    timer.End();

    std::lock_guard<std::mutex> guard(GlobalVariables::DEBUG_OUTPUT_MUTEX);

    Debug::WriteLine("-------------------------------------------------------------");
    Debug::WriteLine("Hash Indexer test:");
    Debug::WriteLine("Row count {}, Costs {}ms", ROW_COUNT, timer.Duration(TimeAccuracy::Millisecond));
    Debug::WriteLine("Results: {}", result->Results->size());
    //Debug::WriteLine("Content:\n{}", indexer.ToString());
    Debug::WriteLine("-------------------------------------------------------------");
}
