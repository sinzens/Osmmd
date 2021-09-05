/*
* Created by Zeng Yinuo, 2021.09.04
*/

#pragma once

#include "RowValue.h"

namespace Osmmd
{
    class OSMMD_CORE_API Indexer : public ISerializable
    {
    public:
        virtual void Insert(const ColumnValue& key, std::shared_ptr<RowValue> value) = 0;

        virtual void Delete(const ColumnValue& key) = 0;

        virtual void Update(const ColumnValue& key, std::shared_ptr<RowValue> value) = 0;

        virtual std::vector<RowValue> Select(const ColumnValue& key) const = 0;
        virtual std::vector<RowValue> Select(std::function<bool(std::shared_ptr<RowValue>)> filter) const = 0;
    };
}
