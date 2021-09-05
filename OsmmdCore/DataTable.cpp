/*
* Created by Zeng Yinuo, 2021.09.05
*/

#include "DataTable.h"
#include "BpTreeIndexer.h"
#include "HashIndexer.h"

Osmmd::DataTable::DataTable()
    : m_primaryIndexer(nullptr)
{
}

Osmmd::DataTable::DataTable(const DataTable& other)
    : m_config(other.m_config)
    , m_rowDefinition(other.m_rowDefinition)
    , m_primaryIndexer(other.m_primaryIndexer)
    , m_indexIndexers(other.m_indexIndexers)
{
}

std::string Osmmd::DataTable::ToString() const
{
    return std::string();
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

    Bytes dataLengthData = Value::FromInteger(static_cast<int32_t>(bytes.size())).GetBytes();

    bytes.insert(bytes.begin(), dataLengthData.begin(), dataLengthData.end());

    return bytes;
}

Osmmd::DataTable Osmmd::DataTable::FromBytes(const Bytes& bytes)
{
    auto configDataBegin = bytes.begin() + sizeof(int32_t);
    auto rowDefinitionDataBegin = configDataBegin + Value::GetLengthFromBytesHead(bytes);

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
    std::shared_ptr<Indexer> primaryIndexer = IndexerFromBytes(config.INDEX_STRATEGY, rowDefinition, *primaryIndexerData);

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
        std::shared_ptr<Indexer> indexer = IndexerFromBytes(config.INDEX_STRATEGY, rowDefinition, *indexIndexerData);

        table.m_indexIndexers.insert({ indexerName, indexer });
    }

    return table;
}

std::shared_ptr<Osmmd::DataTable> Osmmd::DataTable::PtrFromBytes(const Bytes& bytes)
{
    return std::make_shared<DataTable>(DataTable::FromBytes(bytes));
}

std::shared_ptr<Osmmd::Indexer> Osmmd::DataTable::IndexerFromBytes
(
    IndexStrategy indexStrategy,
    const Row& rowDefinition,
    const Bytes& bytes
)
{
    switch (indexStrategy)
    {
    case IndexStrategy::BpTree:
        return BpTreeIndexer::PtrFromBytes(rowDefinition, bytes);
    case IndexStrategy::Hash:
        return HashIndexer::PtrFromBytes(rowDefinition, bytes);
    }
}
