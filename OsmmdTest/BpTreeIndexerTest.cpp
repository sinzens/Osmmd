/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
*/

#include "BpTreeIndexerTest.h"
#include "GlobalVariables.h"

#include "MockDataGenerator.h"

void Osmmd::BpTreeIndexerTest::Test()
{
    constexpr int ROW_COUNT = 10000;

    Row rowDefinition = MockDataGenerator::MockRow();
    BpTreeIndexer indexer = MockDataGenerator::MockBpTreeIndexer(ROW_COUNT, rowDefinition);

    Timer timer;
    timer.Start();

    auto result = indexer.Select({ MockDataGenerator::MockCondition(rowDefinition) }, rowDefinition, rowDefinition);

    timer.End();

    std::lock_guard<std::mutex> guard(GlobalVariables::DEBUG_OUTPUT_MUTEX);

    Debug::WriteLine("-------------------------------------------------------------");
    Debug::WriteLine("BpTree Indexer test:");
    Debug::WriteLine("Costs {}ms", timer.Duration(TimeAccuracy::Millisecond));
    //Debug::WriteLine("Content:\n{}", indexer.ToString());
    Debug::WriteLine("-------------------------------------------------------------");
}
