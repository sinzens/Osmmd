/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#pragma once

#include "Indexer.h"
#include "Row.h"

namespace Osmmd
{
    class OSMMD_CORE_API BpTreeIndexer : public Indexer
    {
    public:
        virtual void Insert(const ColumnValue& key, std::shared_ptr<RowValue> value) override;

        virtual void Delete(const ColumnValue& key) override;

        virtual void Update(const ColumnValue& key, std::shared_ptr<RowValue> value) override;

        virtual std::vector<RowValue> Select(const ColumnValue& key) const override;
        virtual std::vector<RowValue> Select(std::function<bool(std::shared_ptr<RowValue>)> filter) const override;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static BpTreeIndexer FromBytes(const Row& rowDefinition, const Bytes& bytes);
        static std::shared_ptr<BpTreeIndexer> PtrFromBytes(const Row& rowDefinition, const Bytes& bytes);
    };
}
