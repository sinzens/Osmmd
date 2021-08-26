/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    class Driver;

    class Cli
    {
    public:
        Cli(const Cli& other) = delete;
        Cli& operator=(const Cli& other) = delete;

        int Run();

        static Cli& Init(int argc, char* argv[]);
        static Cli& GetInstance();

    private:
        Cli();

        void SetCommandLineArguments(const std::vector<std::string>& args);
        void SetWorkingDirectory(const std::string& directory);

        bool InitEnvironment();

        void PrintHello();
        void PrintBye();

        int RunMessageLoop();

        std::vector<std::string> m_commandLineArgs;
        std::string m_workingDirectory;

        Driver& m_driver;
    };
}
