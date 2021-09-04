/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    class OSMMD_CORE_API ISerializable
    {
    public:
        virtual std::string ToString() const = 0;
        virtual Bytes ToBytes() const = 0;
    };
}
