/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.08
* Edited by Zeng Yinuo, 2021.09.09
*/

#pragma once

#include "Global.h"
#include "../OsmmdCore/Row.h"

namespace Osmmd
{
    class Driver;
    class RowValue;

    class Cli
    {
    public:
        Cli(const Cli& other) = delete;
        Cli& operator=(const Cli& other) = delete;
        ~Cli();

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
        void PrintSelectResults(const Row& rowDefinition, const std::vector<std::shared_ptr<RowValue>>& results);

        int RunMessageLoop();

        void HandleInput(const std::string& input);

        int GetDisplayLength(const Row& rowDefinition, std::shared_ptr<RowValue> row) const;

        std::string GetDisplayString(const Row& rowDefinition, std::shared_ptr<RowValue> row, bool elide = false) const;
        std::string GetTableHeaderDisplayString(const Row& rowDefinition, std::shared_ptr<RowValue> row) const;

        std::vector<std::string> m_commandLineArgs;
        std::string m_workingDirectory;

        Driver& m_driver;
        
        std::ofstream m_logger;
    };
}
