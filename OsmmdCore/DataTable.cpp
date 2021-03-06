/*
* Created by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "DataTable.h"
#include "BpTreeIndexer.h"
#include "HashIndexer.h"
#include "Math.h"

Osmmd::DataTable::DataTable()
    : m_primaryIndexer(this->CreateIndexer())
{
    for (const std::string& indexName : m_config.INDEXES)
    {
        m_indexIndexers.insert({ indexName, this->CreateIndexer() });
    }
}

Osmmd::DataTable::DataTable(const DataTable& other)
    : m_config(other.m_config)
    , m_rowDefinition(other.m_rowDefinition)
    , m_primaryIndexer(other.m_primaryIndexer)
    , m_indexIndexers(other.m_indexIndexers)
{
}

Osmmd::DataTable::DataTable(const DataTableConfiguration& config, const Row& rowDefinition)
    : m_config(config)
    , m_rowDefinition(rowDefinition)
    , m_primaryIndexer(this->CreateIndexer())
{
    for (const std::string& indexName : m_config.INDEXES)
    {
        m_indexIndexers.insert({ indexName, this->CreateIndexer() });
    }
}

const Osmmd::DataTableConfiguration& Osmmd::DataTable::GetConfiguration() const
{
    return m_config;
}

const Osmmd::Row& Osmmd::DataTable::GetRowDefinition() const
{
    return m_rowDefinition;
}

std::shared_ptr<Osmmd::IndexResult> Osmmd::DataTable::Insert(std::shared_ptr<RowValue> value)
{
    for (int i = 0; i < value->Values.size(); i++)
    {
        std::string columnName = m_rowDefinition.ColumnAt(i).Name;

        if (this->IsIndex(columnName))
        {
            std::shared_ptr<RowValue> primaryKeyValue = std::make_shared<RowValue>();
            primaryKeyValue->Values.emplace_back(value->Values.at(this->GetPrimaryKeyIndex()));

            std::shared_ptr<IndexResult> result
                = m_indexIndexers.at(columnName)->Insert(value->Values.at(i), primaryKeyValue);

            if (!result->IsSuccessful())
            {
                return result;
            }
        }
    }

    return m_primaryIndexer->Insert(value->Values.at(this->GetPrimaryKeyIndex()), value);
}

std::shared_ptr<Osmmd::IndexResult> Osmmd::DataTable::Delete(const std::vector<Condition>& conditions)
{
    std::shared_ptr<SelectIndexResult> deleteResult = m_primaryIndexer->Delete(conditions);

    if (!deleteResult->IsSuccessful())
    {
        return deleteResult;
    }

    int primaryKeyIndex = this->GetPrimaryKeyIndex();

    if (deleteResult->Results->size() != 0)
    {
        for (int i = 0; i < m_rowDefinition.Columns.size(); i++)
        {
            std::string columnName = m_rowDefinition.ColumnAt(i).Name;

            if (!this->IsIndex(columnName))
            {
                continue;
            }

            for (std::shared_ptr<RowValue> deletedValue : *(deleteResult->Results))
            {
                std::vector<int> indexs = { 0 };
                Condition condition(ConditionOperator::Equal, indexs, deletedValue->Values.at(primaryKeyIndex));

                std::shared_ptr<SelectIndexResult> result = m_indexIndexers.at(columnName)->Delete({ condition });

                if (!result->IsSuccessful())
                {
                    return result;
                }
            }
        }
    }

    return deleteResult;
}

std::shared_ptr<Osmmd::IndexResult> Osmmd::DataTable::Update
(
    const std::vector<Condition>& conditions,
    const Row& updateRow,
    std::shared_ptr<RowValue> updateValue
)
{
    if (this->UseIndexIndexing(conditions))
    {
        std::string indexName = this->IndexName(conditions.front().ColumnIndexes.front());
        std::shared_ptr<RowValue> rowResult = this->SelectValueWithIndex(indexName, conditions.front().Value);

        if (rowResult)
        {
            std::shared_ptr<IndexResult> updateIndexersResult = this->UpdateIndexers(updateRow, updateValue, rowResult);

            if (!updateIndexersResult->IsSuccessful())
            {
                return updateIndexersResult;
            }

            return std::make_shared<IndexResult>(1, rowResult->Update(updateRow, m_rowDefinition, updateValue));
        }

        return std::make_shared<IndexResult>();
    }

    std::shared_ptr<SelectIndexResult> results
        = m_primaryIndexer->Update(conditions, updateRow, m_rowDefinition, updateValue);

    if (!results->IsSuccessful())
    {
        return results;
    }

    for (std::shared_ptr<RowValue> result : *(results->Results))
    {
        std::shared_ptr<IndexResult> updateIndexersResult = this->UpdateIndexers(updateRow, updateValue, result);

        if (!updateIndexersResult->IsSuccessful())
        {
            return updateIndexersResult;
        }
    }

    return m_primaryIndexer->Update(conditions, updateRow, m_rowDefinition, updateValue);
}

std::shared_ptr<Osmmd::SelectIndexResult> Osmmd::DataTable::Select
(
    const std::vector<Condition>& conditions,
    const Row& selectRow
)
{
    if (this->UseIndexIndexing(conditions))
    {
        std::string indexName = this->IndexName(conditions.front().ColumnIndexes.front());
        std::shared_ptr<RowValue> rowResult = this->SelectValueWithIndex(indexName, conditions.front().Value);

        std::shared_ptr<SelectIndexResult> result = std::make_shared<SelectIndexResult>();

        if (rowResult)
        {
            result->Results->emplace_back(rowResult);
        }

        return result;
    }

    return m_primaryIndexer->Select(conditions, selectRow, m_rowDefinition);
}

std::string Osmmd::DataTable::ToString() const
{
    std::string result;

    result.append(m_config.ToString()).append("\n\n");
    result.append("Primary Key Index:\n").append(m_primaryIndexer->ToString()).append("\n\n");

    for (auto i = m_indexIndexers.begin(); i != m_indexIndexers.end(); i++)
    {
        char buffer[100]{};
        sprintf_s(buffer, "Index (%s):\n", i->first.c_str());

        result.append(buffer).append(i->second->ToString()).append("\n\n");
    }

    return result;
}

Bytes Osmmd::DataTable::ToBytes() const
{
    Bytes bytes;

    Bytes configData = m_config.ToBytes();
    Bytes rowDefinitionData = m_rowDefinition.ToBytes();
    Bytes primaryIndexerData = m_primaryIndexer->ToBytes();

    Bytes indexIndexerCountData = Value::FromInteger(static_cast<int32_t>(m_indexIndexers.size())).GetBytes();

    bytes.insert(bytes.end(), configData.begin(), configData.end());
    bytes.insert(bytes.end(), rowDefinitionData.begin(), rowDefinitionData.end());
    bytes.insert(bytes.end(), primaryIndexerData.begin(), primaryIndexerData.end());
    bytes.insert(bytes.end(), indexIndexerCountData.begin(), indexIndexerCountData.end());

    for (auto i = m_indexIndexers.begin(); i != m_indexIndexers.end(); i++)
    {
        Bytes indexerNameLengthData = Value::FromInteger(static_cast<int32_t>((*i).first.size())).GetBytes();
        Bytes indexerNameData((*i).first.begin(), (*i).first.end());
        Bytes indexIndexerData = (*i).second->ToBytes();

        bytes.insert(bytes.end(), indexerNameLengthData.begin(), indexerNameLengthData.end());
        bytes.insert(bytes.end(), indexerNameData.begin(), indexerNameData.end());
        bytes.insert(bytes.end(), indexIndexerData.begin(), indexIndexerData.end());
    }

    Bytes dataLengthData = Value::FromInteger(static_cast<int32_t>(bytes.size()) + sizeof(int32_t)).GetBytes();

    bytes.insert(bytes.begin(), dataLengthData.begin(), dataLengthData.end());

    return bytes;
}

Osmmd::DataTable Osmmd::DataTable::FromBytes(const Bytes& bytes)
{
    auto configDataBegin = bytes.begin() + sizeof(int32_t);

    auto rowDefinitionDataBegin
        = configDataBegin
        + Value::GetLengthFromBytesHead(Bytes(configDataBegin, configDataBegin + sizeof(int32_t)));

    auto primaryIndexerDataBegin
        = rowDefinitionDataBegin
        + Value::GetLengthFromBytesHead(Bytes(rowDefinitionDataBegin, rowDefinitionDataBegin + sizeof(int32_t)));

    auto indexIndexerCountDataBegin
        = primaryIndexerDataBegin
        + Value::GetLengthFromBytesHead(Bytes(primaryIndexerDataBegin, primaryIndexerDataBegin + sizeof(int32_t)));

    int32_t indexIndexerCount
        = Value::GetLengthFromBytesHead(Bytes(indexIndexerCountDataBegin, indexIndexerCountDataBegin + sizeof(int32_t)));

    std::shared_ptr<Bytes> primaryIndexerData = std::make_shared<Bytes>(primaryIndexerDataBegin, indexIndexerCountDataBegin);

    DataTableConfiguration config = DataTableConfiguration::FromBytes(Bytes(configDataBegin, rowDefinitionDataBegin));

    Row rowDefinition = Row::FromBytes(Bytes(rowDefinitionDataBegin, primaryIndexerDataBegin));

    std::shared_ptr<Indexer> primaryIndexer = IndexerFromBytes
    (
        config.INDEX_STRATEGY,
        rowDefinition.ColumnIndex(config.PRIMARY_KEY),
        rowDefinition,
        *primaryIndexerData
    );

    DataTable table;

    table.m_config = config;
    table.m_rowDefinition = rowDefinition;
    table.m_primaryIndexer = primaryIndexer;

    int indexIndexerDataBlockBeginIndex = indexIndexerCountDataBegin + sizeof(int32_t) - bytes.begin();
    for (int i = 0; i < indexIndexerCount; i++)
    {
        auto indexIndexerDataBlockBegin = bytes.begin() + indexIndexerDataBlockBeginIndex;

        int indexerNameLength
            = Value::GetLengthFromBytesHead(Bytes(indexIndexerDataBlockBegin, indexIndexerDataBlockBegin + sizeof(int32_t)));

        auto indexerNameDataBegin = indexIndexerDataBlockBegin + sizeof(int32_t);
        auto indexIndexerDataBegin = indexerNameDataBegin + indexerNameLength;

        int indexIndexerDataLength
            = Value::GetLengthFromBytesHead(Bytes(indexIndexerDataBegin, indexIndexerDataBegin + sizeof(int32_t)));

        std::shared_ptr<Bytes> indexIndexerData
            = std::make_shared<Bytes>(indexIndexerDataBegin, indexIndexerDataBegin + indexIndexerDataLength);

        std::string indexerName(indexerNameDataBegin, indexIndexerDataBegin);

        std::shared_ptr<Indexer> indexer = IndexerFromBytes
        (
            config.INDEX_STRATEGY,
            0,
            rowDefinition.Sliced(std::vector<std::string>({ config.PRIMARY_KEY })),
            *indexIndexerData
        );

        table.m_indexIndexers.insert({ indexerName, indexer });
    }

    return table;
}

std::shared_ptr<Osmmd::DataTable> Osmmd::DataTable::PtrFromBytes(const Bytes& bytes)
{
    return std::make_shared<DataTable>(DataTable::FromBytes(bytes));
}

Osmmd::DataTable& Osmmd::DataTable::operator=(const DataTable& other)
{
    m_config = other.m_config;
    m_rowDefinition = other.m_rowDefinition;
    m_primaryIndexer = other.m_primaryIndexer;
    m_indexIndexers = other.m_indexIndexers;

    return *this;
}

std::shared_ptr<Osmmd::Indexer> Osmmd::DataTable::IndexerFromBytes
(
    IndexStrategy indexStrategy,
    int keyIndex,
    const Row& rowDefinition,
    const Bytes& bytes
)
{
    switch (indexStrategy)
    {
    case IndexStrategy::BpTree:
        return BpTreeIndexer::PtrFromBytes(keyIndex, rowDefinition, bytes);
    case IndexStrategy::Hash:
        return HashIndexer::PtrFromBytes(keyIndex, rowDefinition, bytes);
    }
}

std::shared_ptr<Osmmd::IndexResult> Osmmd::DataTable::UpdateIndexers
(
    const Row& updateRow,
    std::shared_ptr<RowValue> updateValue,
    std::shared_ptr<RowValue> oldValue
)
{
    for (int i = 0; i < updateRow.Columns.size(); i++)
    {
        std::string columnName = updateRow.ColumnAt(i).Name;

        if (this->IsIndex(columnName))
        {
            int columnIndex = m_rowDefinition.ColumnIndex(columnName);

            std::shared_ptr<IndexResult> result
                = m_indexIndexers.at(columnName)->UpdateKeyword
                (
                    updateValue->Values.at(i),
                    oldValue->Values.at(columnIndex)
                );

            if (!result->IsSuccessful())
            {
                return result;
            }
        }
    }

    return std::make_shared<IndexResult>();
}

std::shared_ptr<Osmmd::Indexer> Osmmd::DataTable::CreateIndexer() const
{
    return this->CreateIndexer(m_config.INDEX_STRATEGY);
}

std::shared_ptr<Osmmd::Indexer> Osmmd::DataTable::CreateIndexer(IndexStrategy indexStrategy) const
{
    switch (indexStrategy)
    {
    case IndexStrategy::BpTree:
        return std::make_shared<BpTreeIndexer>();
    case IndexStrategy::Hash:
        return std::make_shared<HashIndexer>();
    }

    return std::make_shared<HashIndexer>();
}

int Osmmd::DataTable::GetPrimaryKeyIndex() const
{
    return m_rowDefinition.ColumnIndex(m_config.PRIMARY_KEY);
}

bool Osmmd::DataTable::UseIndexIndexing(const std::vector<Condition>& conditions)
{
    return
    (
        conditions.size() == 1 &&
        conditions.front().IsSimpleEqualCondition() &&
        this->IsIndex(conditions.front().ColumnIndexes.front())
    );
}

bool Osmmd::DataTable::IsIndex(int index) const
{
    if (index < 0 || index >= m_rowDefinition.Columns.size())
    {
        return false;
    }

    return m_config.INDEXES.find(m_rowDefinition.ColumnAt(index).Name) != m_config.INDEXES.end();
}

bool Osmmd::DataTable::IsIndex(const std::string& name) const
{
    return m_config.INDEXES.find(name) != m_config.INDEXES.end();
}

std::string Osmmd::DataTable::IndexName(int index) const
{
    std::string columnName = m_rowDefinition.ColumnAt(index).Name;

    if (m_config.INDEXES.find(columnName) == m_config.INDEXES.end())
    {
        return std::string();
    }

    return columnName;
}

bool Osmmd::DataTable::IsPrimaryKey(int index) const
{
    return this->GetPrimaryKeyIndex() == index;
}

bool Osmmd::DataTable::IsPrimaryKey(const std::string& name)
{
    return name == m_config.PRIMARY_KEY;
}

std::shared_ptr<Osmmd::RowValue> Osmmd::DataTable::SelectValueWithIndex
(
    const std::string& indexName,
    std::shared_ptr<ColumnValue> indexValue
)
{
    std::shared_ptr<RowValue> primaryKeyRowValue = m_indexIndexers.at(indexName)->DirectSelect(indexValue);

    if (!primaryKeyRowValue)
    {
        return nullptr;
    }

    return m_primaryIndexer->DirectSelect(primaryKeyRowValue->Values.front());
}
