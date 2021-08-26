/*
* Created by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "Global.h"
#include "DriverConfiguration.h"

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

        static Driver& GetInstance();

    private:
        Driver();

        void WriteConfiguration() const;
        void ReadConfiguration();

        std::string m_workingDirectory;

        DriverConfiguration m_config;
    };
}
