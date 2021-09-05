/*
* Created by Zeng Yinuo, 2021.09.05
*/

#pragma once

#include "ISerializable.h"

namespace Osmmd
{
    struct OSMMD_CORE_API DatabaseConfiguration : public ISerializable
    {
        std::string NAME;
        std::map<std::string, std::string> TABLES;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static DatabaseConfiguration FromBytes(const Bytes& bytes);

        DatabaseConfiguration& operator=(const DatabaseConfiguration& other);
    };
}
