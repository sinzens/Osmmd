/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "DriverConfiguration.h"
#include "PerformanceConfiguration.h"

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

        static Driver& GetInstance();

    private:
        Driver();

        void WriteConfiguration() const;
        void ReadConfiguration();

        std::string m_workingDirectory;

        DriverConfiguration m_config;
        PerformanceConfiguration m_performance;
    };
}
