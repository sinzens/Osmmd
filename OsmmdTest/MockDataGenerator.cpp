/*
* Created by Zeng Yinuo, 2021.09.04
*/

#include "MockDataGenerator.h"

#include "../OsmmdCore/Random.h"

Osmmd::Column Osmmd::MockDataGenerator::MockColumn()
{
    Column column;

    char buffer[20];

    sprintf_s(buffer, "Column%s", Random::RandomString(5).c_str());

    Value value = Random::RandomValue();

    column.Name = buffer;
    column.Type = value.GetType();
    column.Length = value.GetLength();

    return column;
}

Osmmd::ColumnValue Osmmd::MockDataGenerator::MockColumnValue()
{
    ColumnValue column;
    column.Data = Random::RandomValue();
    return column;
}

Osmmd::Row Osmmd::MockDataGenerator::MockRow()
{
    return MockRow(Random::RandomInteger(3, 10));
}

Osmmd::Row Osmmd::MockDataGenerator::MockRow(int columnCount)
{
    Row row;

    for (int i = 0; i < columnCount; i++)
    {
        row.Columns.emplace_back(MockColumn());
    }

    return row;
}

Osmmd::RowValue Osmmd::MockDataGenerator::MockRowValue(const Row& rowDefinition)
{
    RowValue row;

    for (const Column& column : rowDefinition.Columns)
    {
        ColumnValue value;
        value.Data = Random::RandomValue(column.Type);
        row.Values.emplace_back(value);
    }

    return row;
}

std::vector<Osmmd::RowValue> Osmmd::MockDataGenerator::MockRowValues()
{
    return MockRowValues(Random::RandomInteger(3, 20));
}

std::vector<Osmmd::RowValue> Osmmd::MockDataGenerator::MockRowValues(int rowCount)
{
    return MockRowValues(MockRow(), rowCount);
}

std::vector<Osmmd::RowValue> Osmmd::MockDataGenerator::MockRowValues(const Row& rowDefinition, int rowCount)
{
    std::vector<RowValue> values;

    for (int i = 0; i < rowCount; i++)
    {
        values.emplace_back(MockRowValue(rowDefinition));
    }

    return values;
}
