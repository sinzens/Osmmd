/*
* Created by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "Row.h"
#include "Indexer.h"
#include "IndexResult.h"
#include "DataTableConfiguration.h"

namespace Osmmd
{
    class OSMMD_CORE_API DataTable : public ISerializable
    {
    public:
        DataTable();
        DataTable(const DataTable& other);
        DataTable(const DataTableConfiguration& config, const Row& rowDefinition);

        std::shared_ptr<IndexResult> Insert(std::shared_ptr<RowValue> value);

        std::shared_ptr<IndexResult> Delete(const std::vector<Condition>& conditions);

        std::shared_ptr<IndexResult> Update
        (
            const std::vector<Condition>& conditions,
            const Row& updateRow,
            std::shared_ptr<RowValue> updateValue
        );

        std::shared_ptr<SelectIndexResult> Select
        (
            const std::vector<Condition>& conditions,
            const Row& selectRow
        );

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static DataTable FromBytes(const Bytes& bytes);
        static std::shared_ptr<DataTable> PtrFromBytes(const Bytes& bytes);

        DataTable& operator=(const DataTable& other);

    private:
        static std::shared_ptr<Indexer> IndexerFromBytes
        (
            IndexStrategy indexStrategy,
            const Row& rowDefinition,
            const Bytes& bytes
        );

        std::shared_ptr<Indexer> CreateIndexer() const;
        std::shared_ptr<Indexer> CreateIndexer(IndexStrategy indexStrategy) const;

        int GetPrimaryKeyIndex() const;

        bool UseIndexIndexing(const std::vector<Condition>& conditions);

        bool IsIndex(int index) const;
        bool IsIndex(const std::string& name) const;

        std::string IndexName(int index) const;

        std::shared_ptr<RowValue> SelectValueWithIndex
        (
            const std::string& indexName,
            std::shared_ptr<ColumnValue> indexValue
        );

        DataTableConfiguration m_config;

        Row m_rowDefinition;

        std::shared_ptr<Indexer> m_primaryIndexer;
        std::map<std::string, std::shared_ptr<Indexer>> m_indexIndexers;
    };
}
