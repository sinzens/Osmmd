/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "DatabaseConfiguration.h"
#include "DataTable.h"

namespace Osmmd
{
    class OSMMD_CORE_API Database : public ISerializable
    {
    public:
        Database(const DatabaseConfiguration& config);

        std::shared_ptr<DataTable> GetTable(const std::string& name);

        std::string CreateTable(const DataTableConfiguration& config, const Row& rowDefinition);
        std::string DeleteTable(const std::string& name);

        void RefreshConfiguration();
        void RefreshConfiguration(const DatabaseConfiguration& config);

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static Database FromBytes(const Bytes& bytes);
        static std::shared_ptr<Database> PtrFromBytes(const Bytes& bytes);

        static std::shared_ptr<DataTable> ReadTableFromFile(const std::string& path);
        static void WriteTableToFile(const std::string& path, std::shared_ptr<DataTable> table);

    private:
        std::string GetConfigFilePath() const;
        std::string GetWorkingDirectory() const;

        DatabaseConfiguration m_config;

        std::map<std::string, std::shared_ptr<DataTable>> m_tables;
    };
}
