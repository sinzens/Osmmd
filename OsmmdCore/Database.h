/*
* Created by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    class OSMMD_CORE_API Database
    {
    public:
        Database(const std::string& name);

        const std::string& GetName() const;

    private:
        std::string m_name;
    };
}
