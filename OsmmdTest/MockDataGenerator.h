/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
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
        static ColumnValue MockColumnValue(const Column& column);

        static Row MockRow();
        static Row MockRow(int columnCount);

        static RowValue MockRowValue(const Row& rowDefinition);

        static std::vector<RowValue> MockRowValues();
        static std::vector<RowValue> MockRowValues(int rowCount);
        static std::vector<RowValue> MockRowValues(int rowCount, const Row& rowDefinition);

        static DataTableConfiguration MockDataTableConfiguration();

        static BpTreeIndexer MockBpTreeIndexer();
        static BpTreeIndexer MockBpTreeIndexer(int rowCount);
        static BpTreeIndexer MockBpTreeIndexer(int rowCount, const Row& rowDefinition);

        static HashIndexer MockHashIndexer();
        static HashIndexer MockHashIndexer(int rowCount);
        static HashIndexer MockHashIndexer(int rowCount, const Row& rowDefinition);

        static Condition MockCondition(const Row& rowDefinition);
        static Condition MockCondition(std::shared_ptr<RowValue> value);
    };
}
