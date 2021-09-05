/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#include "BpTreeIndexerTest.h"
#include "GlobalVariables.h"

#include "MockDataGenerator.h"

void Osmmd::BpTreeIndexerTest::Test()
{
    Timer timer;
    timer.Start();

    BpTreeIndexer indexer = MockDataGenerator::MockBpTreeIndexer();

    timer.End();

    std::lock_guard<std::mutex> guard(GlobalVariables::DEBUG_OUTPUT_MUTEX);

    Debug::WriteLine("-------------------------------------------------------------");
    Debug::WriteLine("BpTree Indexer test:");
    Debug::WriteLine("Costs {}ms", timer.Duration(TimeAccuracy::Millisecond));
    Debug::WriteLine("Content:\n{}", indexer.ToString());
    Debug::WriteLine("-------------------------------------------------------------");
}
