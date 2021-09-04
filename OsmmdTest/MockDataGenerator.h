/*
* Created by Zeng Yinuo, 2021.09.04
*/

#pragma once

#include "../OsmmdCore/Column.h"
#include "../OsmmdCore/ColumnValue.h"
#include "../OsmmdCore/Row.h"
#include "../OsmmdCore/RowValue.h"

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
    };
}
