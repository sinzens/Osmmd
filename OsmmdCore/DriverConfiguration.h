/*
* Created by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "ISerializable.h"

namespace Osmmd
{
    struct OSMMD_CORE_API DriverConfiguration : public ISerializable
    {
        std::string NAME;
        std::map<std::string, std::string> DATABASES;

        std::string ToBytes() const override;
        static DriverConfiguration FromBytes(const std::string& bytes);

        DriverConfiguration& operator=(const DriverConfiguration& other);
    };
}
