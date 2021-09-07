/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "DriverConfiguration.h"
#include "PerformanceConfiguration.h"

#include "CommandExecutor.h"

namespace Osmmd
{
    class OSMMD_CORE_API Driver
    {
    public:
        Driver(const Driver& other) = delete;
        Driver& operator=(const Driver& other) = delete;

        void SetWorkingDirectory(const std::string& directory);

        void RefreshConfiguration();
        void RefreshConfiguration(const DriverConfiguration& config);

        bool InitEnvironment();
        bool InitConfiguration();

        std::string GetWorkingDirectory() const;
        std::string GetConfigurationPath() const;

        const DriverConfiguration& GetConfiguration() const;
        const PerformanceConfiguration& GetPerformance() const;

        void ExecuteSqls(const std::vector<std::string>& sqls);

        static Driver& GetInstance();

    private:
        Driver();

        void WriteConfiguration() const;
        void ReadConfiguration();

        std::string m_workingDirectory;

        DriverConfiguration m_config;
        PerformanceConfiguration m_performance;

        std::unique_ptr<CommandExecutor> m_executor;
    };
}
