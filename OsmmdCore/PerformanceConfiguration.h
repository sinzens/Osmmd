/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "ISerializable.h"

namespace Osmmd
{
    struct OSMMD_CORE_API PerformanceConfiguration : public ISerializable
    {
        bool TIMING = true;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static PerformanceConfiguration FromBytes(const Bytes& bytes);

        PerformanceConfiguration& operator=(const PerformanceConfiguration& other);
    };
}

