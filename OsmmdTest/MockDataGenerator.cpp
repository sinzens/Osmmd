/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#include "MockDataGenerator.h"

Osmmd::Column Osmmd::MockDataGenerator::MockColumn()
{
    char buffer[20];
    sprintf_s(buffer, "Column%s", Random::RandomString(5).c_str());

    Value value = Random::RandomValue();

    return Column(buffer, value.GetLength(), value.GetType());
}

Osmmd::ColumnValue Osmmd::MockDataGenerator::MockColumnValue()
{
    return ColumnValue(Random::RandomValue());
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
        row.Values.emplace_back(std::make_shared<ColumnValue>(Random::RandomValue(column.Type)));
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

Osmmd::DataTableConfiguration Osmmd::MockDataGenerator::MockDataTableConfiguration()
{
    DataTableConfiguration config;

    config.NAME = Random::RandomString(10);
    config.PRIMARY_KEY = Random::RandomString(5);
    config.INDEX_STRATEGY = Random::RandomIndexStrategy();

    int randomIndexCount = Random::RandomInteger(0, 5);

    for (int i = 0; i < randomIndexCount; i++)
    {
        config.INDEXES.insert(Random::RandomString(10));
    }

    return config;
}

Osmmd::BpTreeIndexer Osmmd::MockDataGenerator::MockBpTreeIndexer()
{
    return MockBpTreeIndexer(Random::RandomInteger(1, 100));
}

Osmmd::BpTreeIndexer Osmmd::MockDataGenerator::MockBpTreeIndexer(int rowCount)
{
    BpTreeIndexer indexer;

    std::vector<RowValue> values = MockRowValues(rowCount);
    int randomPrimaryKeyIndex = Random::RandomInteger(0, values.front().Values.size());

    for (const RowValue& value : values)
    {
        indexer.Insert(*(value.Values.at(randomPrimaryKeyIndex)), std::make_shared<RowValue>(value));
    }

    return indexer;
}

Osmmd::HashIndexer Osmmd::MockDataGenerator::MockHashIndexer()
{
    return MockHashIndexer(Random::RandomInteger(1, 100));
}

Osmmd::HashIndexer Osmmd::MockDataGenerator::MockHashIndexer(int rowCount)
{
    HashIndexer indexer;

    std::vector<RowValue> values = MockRowValues(rowCount);
    int randomPrimaryKeyIndex = Random::RandomInteger(0, values.front().Values.size());

    for (const RowValue& value : values)
    {
        indexer.Insert(*(value.Values.at(randomPrimaryKeyIndex)), std::make_shared<RowValue>(value));
    }

    return indexer;
}
