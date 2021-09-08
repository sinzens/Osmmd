/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "DriverConfiguration.h"
#include "PerformanceConfiguration.h"
#include "Database.h"

#include "CommandExecutor.h"

namespace Osmmd
{
    class OSMMD_CORE_API Driver
    {
    public:
        Driver(const Driver& other) = delete;
        Driver& operator=(const Driver& other) = delete;

        void SetWorkingDirectory(const std::string& directory);
        std::string SetCurrentDatabase(const std::string& name);

        void RefreshConfiguration();
        void RefreshConfiguration(const DriverConfiguration& config);

        bool InitEnvironment();
        bool InitConfiguration();

        std::string GetWorkingDirectory() const;
        std::string GetConfigurationPath() const;

        const DriverConfiguration& GetConfiguration() const;
        const PerformanceConfiguration& GetPerformance() const;

        std::shared_ptr<Database> GetDatabase(const std::string& name) const;
        std::shared_ptr<Database> GetCurrentDatabase() const;

        std::string CreateDatabase(const std::string& name);
        std::string DeleteDatabase(const std::string& name);

        void ExecuteSqls(const std::vector<std::string>& sqls);

        static Driver& GetInstance();

        static std::shared_ptr<Database> ReadDatabaseFromFile(const std::string& path);

    private:
        Driver();

        void WriteConfiguration() const;
        void ReadConfiguration();

        std::string m_workingDirectory;
        std::string m_currentDatabase;

        DriverConfiguration m_config;
        PerformanceConfiguration m_performance;

        std::map<std::string, std::shared_ptr<Database>> m_databases;

        std::unique_ptr<CommandExecutor> m_executor;
    };
}
