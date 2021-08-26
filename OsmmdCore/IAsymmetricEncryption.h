/*
* Created by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    class OSMMD_CORE_API IAsymmetricEncryption
    {
    public:
        virtual std::string Encode(const std::string& bytes) const = 0;
    };
}
