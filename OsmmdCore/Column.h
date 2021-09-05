/*
* Created by Zeng Yinuo, 2021.09.01
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#pragma once

#include "Value.h"

namespace Osmmd
{
    struct OSMMD_CORE_API Column : public ISerializable
    {
        std::string Name;
        int Length;

        DataType Type;

        Column();
        Column(const Column& other);
        Column(const std::string& name, int length, DataType type);

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static Column FromBytes(const Bytes& bytes);

        Column& operator=(const Column& other);
    };
}
