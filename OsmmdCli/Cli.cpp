/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "Cli.h"
#include "CommandLineParser.h"

#include "../OsmmdCore/Driver.h"

constexpr const char CLI_INPUT_PREFIX[] = "Osmmd Cli >> ";

Osmmd::Cli::Cli()
    : m_driver(Driver::GetInstance())
{
}

int Osmmd::Cli::Run()
{
    this->InitEnvironment();
    return this->RunMessageLoop();
}

Osmmd::Cli& Osmmd::Cli::Init(int argc, char* argv[])
{
    Cli& cli = Cli::GetInstance();
    cli.SetCommandLineArguments(CommandLineParser::GetInstance().ParseArguments(argc, argv));

    constexpr const char* WORKING_DIRECTORY = ".";
    cli.SetWorkingDirectory(std::filesystem::absolute(std::filesystem::path(WORKING_DIRECTORY)).u8string());
    
    return cli;
}

Osmmd::Cli& Osmmd::Cli::GetInstance()
{
    static Cli cli;
    return cli;
}

void Osmmd::Cli::SetCommandLineArguments(const std::vector<std::string>& args)
{
    m_commandLineArgs = args;
}

void Osmmd::Cli::SetWorkingDirectory(const std::string& directory)
{
    m_workingDirectory = directory;
    m_driver.SetWorkingDirectory(directory);
}

bool Osmmd::Cli::InitEnvironment()
{
    return m_driver.InitEnvironment();
}

void Osmmd::Cli::PrintHello()
{
    std::cout << "Osmmd --------------------------------------------------- Start" << std::endl << std::endl;
}

void Osmmd::Cli::PrintBye()
{
    std::cout << std::endl << "Osmmd --------------------------------------------------- End" << std::endl;
}

int Osmmd::Cli::RunMessageLoop()
{
    this->PrintHello();

    while (true)
    {
        std::cout << CLI_INPUT_PREFIX;

        std::string currentInput;
        std::getline(std::cin, currentInput);

        if (StringHelper(currentInput).ToSqlCompatible().StartsWith("quit"))
        {
            break;
        }
    }

    this->PrintBye();

    return 0;
}
