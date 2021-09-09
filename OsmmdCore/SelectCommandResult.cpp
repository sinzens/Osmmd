/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
* Edited by Zeng Yinuo, 2021.09.09
*/

#include "SelectCommandResult.h"

Osmmd::SelectCommandResult::SelectCommandResult(const SelectCommandResult& other)
    : CommandResult(other)
    , RowDefinition(other.RowDefinition)
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
    const Row& rowDefinition,
    std::shared_ptr<std::vector<std::shared_ptr<RowValue>>> results
)
    : CommandResult(type, row, col, successful, message, time)
    , RowDefinition(rowDefinition)
    , Results(results)
{
}

std::string Osmmd::SelectCommandResult::ToString() const
{
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
    this->RowDefinition = other.RowDefinition;
    this->Results = other.Results;

    return *this;
}
