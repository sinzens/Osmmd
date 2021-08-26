/*
* Created by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "ISerializable.h"

namespace Osmmd
{
    struct OSMMD_CORE_API PerformanceConfiguration : ISerializable
    {
        bool TIMING = false;

        std::string ToBytes() const override;
        static PerformanceConfiguration FromBytes(const std::string& bytes);

        PerformanceConfiguration& operator=(const PerformanceConfiguration& other);
    };
}

