/*
* Created by Zeng Yinuo, 2021.09.06
*/

#include "SelectCommandResult.h"

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
