/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "DatabaseConfiguration.h"

namespace Osmmd
{
    class OSMMD_CORE_API Database : public ISerializable
    {
    public:
        Database(const DatabaseConfiguration& config);

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static Database FromBytes(const Bytes& bytes);
        static std::shared_ptr<Database> PtrFromBytes(const Bytes& bytes);

    private:
        DatabaseConfiguration m_config;
    };
}
