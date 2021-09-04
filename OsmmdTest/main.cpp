/*
* Created by Zeng Yinuo, 2021.09.04
*/

#include "ColumnByteConvertionTest.h"
#include "RowByteConvertionTest.h"
#include "ColumnValueByteConvertionTest.h"
#include "RowValueByteConvertionTest.h"

using namespace Osmmd;

int main()
{
    std::vector<std::shared_future<void>> testThreads =
    {
        //std::async(ColumnByteConvertionTest::Test),
        //std::async(RowByteConvertionTest::Test),
        //std::async(ColumnValueByteConvertionTest::Test),
        //std::async(RowValueByteConvertionTest::Test)
    };

    for (const std::shared_future<void>& thread : testThreads)
    {
        thread.wait();
    }
}
