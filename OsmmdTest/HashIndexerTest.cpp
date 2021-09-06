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

    HashIndexer indexer = MockDataGenerator::MockHashIndexer(ROW_COUNT);

    Timer timer;
    timer.Start();

    auto results = indexer.Select
    ([](std::shared_ptr<RowValue> row) -> bool
        {
            auto &value = row->Values.at(0);
            if (value->Data.GetType() == DataType::Integer)
            {
                return *(value) > Value(10000000);
            }
            
            return *(value) > Value("2345678901");
        }
    );

    timer.End();

    std::lock_guard<std::mutex> guard(GlobalVariables::DEBUG_OUTPUT_MUTEX);

    Debug::WriteLine("-------------------------------------------------------------");
    Debug::WriteLine("Hash Indexer test:");
    Debug::WriteLine("Row count {}, Costs {}ms", ROW_COUNT, timer.Duration(TimeAccuracy::Millisecond));
    Debug::WriteLine("Results: {}", results->Results->size());
    //Debug::WriteLine("Content:\n{}", indexer.ToString());
    Debug::WriteLine("-------------------------------------------------------------");
}
