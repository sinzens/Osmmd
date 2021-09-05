/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    class MockDataGenerator
    {
    public:
        static Column MockColumn();

        static ColumnValue MockColumnValue();

        static Row MockRow();
        static Row MockRow(int columnCount);

        static RowValue MockRowValue(const Row& rowDefinition);

        static std::vector<RowValue> MockRowValues();
        static std::vector<RowValue> MockRowValues(int rowCount);
        static std::vector<RowValue> MockRowValues(const Row& rowDefinition, int rowCount);

        static DataTableConfiguration MockDataTableConfiguration();

        static BpTreeIndexer MockBpTreeIndexer();
        static BpTreeIndexer MockBpTreeIndexer(int rowCount);

        static HashIndexer MockHashIndexer();
        static HashIndexer MockHashIndexer(int rowCount);
    };
}
