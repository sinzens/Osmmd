/*
* Created by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "ISymmetricEncryption.h"

namespace Osmmd
{
    class OSMMD_CORE_API DesEncryption : public ISymmetricEncryption
    {
    public:
        std::string Encode(const std::string& bytes) const override;
        std::string Decode(const std::string& bytes) const override;
    };
}
