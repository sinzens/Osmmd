/*
* Created by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "ISerializable.h"
#include "IndexStrategy.h"

namespace Osmmd
{
    struct OSMMD_CORE_API DataTableConfiguration : public ISerializable
    {
        std::string NAME;
        std::string PRIMARY_KEY;
        std::set<std::string> INDEXES;

        IndexStrategy INDEX_STRATEGY = IndexStrategy::Hash;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static DataTableConfiguration FromBytes(const Bytes& bytes);

        DataTableConfiguration& operator=(const DataTableConfiguration& other);
    };
}
