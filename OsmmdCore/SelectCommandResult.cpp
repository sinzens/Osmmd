/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "SelectCommandResult.h"

Osmmd::SelectCommandResult::SelectCommandResult(const SelectCommandResult& other)
    : CommandResult(other)
    , Results(other.Results)
{
}

Osmmd::SelectCommandResult::SelectCommandResult
(
    CommandType type,
    int row,
    int col,
    bool successful,
    const std::string& message,
    double time,
    std::shared_ptr<std::vector<std::shared_ptr<RowValue>>> results
)
    : CommandResult(type, row, col, successful, message, time)
    , Results(results)
{
}

std::string Osmmd::SelectCommandResult::ToString() const
{
    /*static constexpr const char SPLIT_LINE[] = "-------------------------------------------------------------";

    std::string result = SPLIT_LINE;
    result.append("\n");

    for (std::shared_ptr<RowValue> value : *(this->Results))
    {
        result.append("\t").append(value->ToString()).append("\n");
    }

    result.append(SPLIT_LINE).append("\n").append(CommandResult::ToString());

    return result;*/
    return CommandResult::ToString();
}

Osmmd::SelectCommandResult& Osmmd::SelectCommandResult::operator=(const SelectCommandResult& other)
{
    this->Type = other.Type;
    this->AffectRowCount = other.AffectRowCount;
    this->AffectColCount = other.AffectColCount;
    this->Successful = other.Successful;
    this->Message = other.Message;
    this->TimeElapse = other.TimeElapse;
    this->Results = other.Results;

    return *this;
}
