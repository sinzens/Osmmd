/*
* Created by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "ISerializable.h"

namespace Osmmd
{
    struct OSMMD_CORE_API CommandResult : public ISerializable
    {
        int affectRowCount;
        int affectColCount;
        bool successful;
        std::string message;
        float timeElapse;

        std::string ToBytes() const override;
    };
}
