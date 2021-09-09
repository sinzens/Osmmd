/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.08
* Edited by Zeng Yinuo, 2021.09.09
*/

#include "Cli.h"
#include "CommandLineParser.h"

#include "../OsmmdCore/Driver.h"
#include "../OsmmdCore/SelectCommandResult.h"

static constexpr const char CLI_INPUT_PREFIX[] = "Osmmd Cli >> ";
static constexpr const char HELLO[] = "Osmmd -------------------------------------------------------------------------------------------- Start";
static constexpr const char BYE[] = "Osmmd -------------------------------------------------------------------------------------------- End";

static constexpr int MAX_DISPLAY_RESULT = 100;

Osmmd::Cli::Cli()
    : m_driver(Driver::GetInstance())
{
}

Osmmd::Cli::~Cli()
{
    m_logger.close();
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
    std::filesystem::path logPath = std::filesystem::path(m_workingDirectory).append("osmmd_log.log");
    m_logger.open(logPath, std::ios::app);

    return m_driver.InitEnvironment();
}

void Osmmd::Cli::PrintHello()
{
    std::cout << HELLO << std::endl << std::endl;
}

void Osmmd::Cli::PrintBye()
{
    std::cout << std::endl << BYE << std::endl;
}

void Osmmd::Cli::PrintSelectResults(const Row& rowDefinition, const std::vector<std::shared_ptr<RowValue>>& results)
{
    std::string row = this->GetTableHeaderDisplayString
    (
        rowDefinition, results.size() == 0 ? nullptr : results.front()
    );

    if (results.size() == 0)
    {
        std::cout << std::endl << row << std::endl <<
            std::string("* --------------------- *\n") +
            std::string("|       No Results      |\n") +
            std::string("* --------------------- *")
        << std::endl << std::endl;

        m_logger << std::endl << row << std::endl <<
            std::string("* --------------------- *\n") +
            std::string("|       No Results      |\n") +
            std::string("* --------------------- *")
        << std::endl << std::endl;

        return;
    }

    int length = GetDisplayLength(rowDefinition, results.front());

    std::string border = std::string("*") + std::string(length - 2, '-') + std::string("*");

    std::cout << std::endl << row << std::endl;
    std::cout << border << std::endl;

    m_logger << std::endl << row << std::endl;
    m_logger << border << std::endl;

    if (results.size() <= MAX_DISPLAY_RESULT)
    {
        for (std::shared_ptr<RowValue> row : results)
        {
            std::string str = this->GetDisplayString(rowDefinition, row);

            std::cout << str << std::endl;
            m_logger << str << std::endl;
        }
    }
    else
    {
        int firstElide = MAX_DISPLAY_RESULT;

        if (results.size() - 2 < firstElide)
        {
            firstElide = results.size() - 2;
        }

        for (int i = 0; i < firstElide; i++)
        {
            std::shared_ptr<RowValue> row = results.at(i);
            std::string str = this->GetDisplayString(rowDefinition, row);

            std::cout << str << std::endl;
            m_logger << str << std::endl;
        }

        std::string elide = this->GetDisplayString(rowDefinition, results.at(firstElide), true);

        std::cout << border << std::endl;
        std::cout << elide << std::endl;
        std::cout << border << std::endl;

        m_logger << border << std::endl;
        m_logger << elide << std::endl;
        m_logger << border << std::endl;

        std::string last = this->GetDisplayString(rowDefinition, results.back());
        std::cout << last << std::endl;
        m_logger << last << std::endl;
    }

    std::cout << border << std::endl;
    std::cout << std::endl;

    m_logger << border << std::endl;
    m_logger << std::endl;
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

        try
        {
            m_logger << "User input: " << currentInput << " ------------------------------------------------" << std::endl;

            this->HandleInput(currentInput);
        }
        catch (const std::exception& error)
        {
            std::cerr << error.what() << std::endl;
            m_logger << error.what() << std::endl;
        }
    }

    this->PrintBye();

    return 0;
}

void Osmmd::Cli::HandleInput(const std::string& input)
{
    StringHelper currentInputStr = StringHelper(input);

    if (currentInputStr.Removed(";").Trimmed().GetLength() == 0)
    {
        return;
    }

    std::vector<std::string> sqls = currentInputStr.Contains(";")
        ? currentInputStr.Split(";")
        : std::vector<std::string>({ currentInputStr.GetString() });

    std::vector<std::shared_ptr<CommandResult>> results = m_driver.ExecuteSqls(sqls);

    for (std::shared_ptr<CommandResult> result : results)
    {
        if (!result->Successful)
        {
            std::string error = result->ToString();

            std::cerr << std::endl << error << std::endl << std::endl;
            m_logger << std::endl << error << std::endl << std::endl;

            continue;
        }

        if
        (
            result->Type == CommandType::Insert ||
            result->Type == CommandType::Delete ||
            result->Type == CommandType::Update ||
            result->Type == CommandType::Select
        )
        {
            std::string resultStr = result->ToString();

            std::cout << std::endl << resultStr << std::endl << std::endl;
            m_logger << std::endl << resultStr << std::endl << std::endl;
        }

        if (result->Type == CommandType::Select)
        {
            SelectCommandResult* selectResult = dynamic_cast<SelectCommandResult*>(result.get());

            if (selectResult && selectResult->Results)
            {
                this->PrintSelectResults(selectResult->RowDefinition, *(selectResult->Results));
            }
        }
    }
}

int Osmmd::Cli::GetDisplayLength(const Row& rowDefinition, std::shared_ptr<RowValue> row) const
{
    return GetDisplayString(rowDefinition, row).size();
}

std::string Osmmd::Cli::GetDisplayString(const Row& rowDefinition, std::shared_ptr<RowValue> row, bool elide) const
{
    std::string str;

    for (auto i = row->Values.begin(); i != row->Values.end(); i++)
    {
        std::shared_ptr<ColumnValue> value = (*i);

        int length = value->GetLength();
        if (value->GetType() == DataType::Integer || value->GetType() == DataType::Double)
        {
            length = 10;
        }

        if (value->GetType() == DataType::DateTime)
        {
            length = 21;
        }

        int columnNameLength = rowDefinition.ColumnAt(i - row->Values.begin()).Name.size();
        
        if (length <= columnNameLength)
        {
            length = columnNameLength + 2;
        }

        char buffer[1000]{};
        sprintf_s(buffer, "| %*s ", length, value->ToString().c_str());

        str.append(buffer);

        if (i == row->Values.end() - 1)
        {
            str.append("|");
        }
    }

    if (elide)
    {
        int leftBlankLength = (str.size() - 5) / 2;
        int rightBlankLength = ((str.size() - 5) & 1) ? leftBlankLength + 1 : leftBlankLength;

        return std::string("|") + std::string(leftBlankLength, ' ') + "..." + std::string(rightBlankLength, ' ') + "|";
    }

    return str;
}

std::string Osmmd::Cli::GetTableHeaderDisplayString(const Row& rowDefinition, std::shared_ptr<RowValue> row) const
{
    if (!row)
    {
        return "* --------------------- *\n|                       |";
    }

    int length = this->GetDisplayLength(rowDefinition, row);
    std::string border = std::string("*") + std::string(length - 2, '-') + std::string("*");
    std::string result = border.append("\n");

    for (int i = 0; i < rowDefinition.Columns.size(); i++)
    {
        const Column& column = rowDefinition.ColumnAt(i);
        std::shared_ptr<ColumnValue> value = row->Values.at(i);

        int nameLength = value->GetLength();
        if (value->GetType() == DataType::Integer || value->GetType() == DataType::Double)
        {
            nameLength = 10;
        }

        if (value->GetType() == DataType::DateTime)
        {
            nameLength = 21;
        }

        int columnNameLength = column.Name.size();

        if (nameLength <= columnNameLength)
        {
            nameLength = columnNameLength + 2;
        }

        char buffer[1000]{};
        sprintf_s(buffer, "| %*s ", nameLength, column.Name.c_str());

        result.append(buffer);

        if (i == rowDefinition.Columns.size() - 1)
        {
            result.append("|");
        }
    }

    return result;
}
