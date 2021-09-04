/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
*/

#pragma once

#include "ISerializable.h"

namespace Osmmd
{
    struct OSMMD_CORE_API DriverConfiguration : public ISerializable
    {
        std::string NAME;
        std::map<std::string, std::string> DATABASES;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static DriverConfiguration FromBytes(const Bytes& bytes);

        DriverConfiguration& operator=(const DriverConfiguration& other);
    };
}
