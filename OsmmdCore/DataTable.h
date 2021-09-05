/*
* Created by Zeng Yinuo, 2021.09.05
*/

#pragma once

#include "Row.h"
#include "Indexer.h"
#include "DataTableConfiguration.h"

namespace Osmmd
{
    class OSMMD_CORE_API DataTable : public ISerializable
    {
    public:
        DataTable();
        DataTable(const DataTable& other);

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static DataTable FromBytes(const Bytes& bytes);
        static std::shared_ptr<DataTable> PtrFromBytes(const Bytes& bytes);

    private:
        static std::shared_ptr<Indexer> IndexerFromBytes
        (
            IndexStrategy indexStrategy,
            const Row& rowDefinition,
            const Bytes& bytes
        );

        DataTableConfiguration m_config;

        Row m_rowDefinition;

        std::shared_ptr<Indexer> m_primaryIndexer;
        std::map<std::string, std::shared_ptr<Indexer>> m_indexIndexers;
    };
}
