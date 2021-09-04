/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
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

        std::string ToString() const override;
        Bytes ToBytes() const override;
    };
}
