/*
* Created by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    class OSMMD_CORE_API ISerializable
    {
    public:
        virtual std::string ToBytes() const = 0;
    };
}
