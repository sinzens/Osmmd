/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#include "ColumnByteConvertionTest.h"
#include "RowByteConvertionTest.h"
#include "ColumnValueByteConvertionTest.h"
#include "RowValueByteConvertionTest.h"

#include "BpTreeIndexerTest.h"
#include "HashIndexerTest.h"

using namespace Osmmd;

int main()
{
    std::vector<std::shared_future<void>> testThreads =
    {
        std::async(ColumnByteConvertionTest::Test),
        std::async(RowByteConvertionTest::Test),
        std::async(ColumnValueByteConvertionTest::Test),
        std::async(RowValueByteConvertionTest::Test),
        //std::async(BpTreeIndexerTest::Test)
    };

    for (const std::shared_future<void>& thread : testThreads)
    {
        thread.wait();
    }
}
