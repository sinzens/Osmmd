/*
* Created by Zeng Yinuo, 2021.09.01
* Edited by Zeng Yinuo, 2021.09.04
*/

#pragma once

#include "Value.h"

namespace Osmmd
{
    struct OSMMD_CORE_API Column : public ISerializable
    {
        std::string Name;
        int32_t Length;

        DataType Type;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static Column FromBytes(const Bytes& bytes);
    };
}
