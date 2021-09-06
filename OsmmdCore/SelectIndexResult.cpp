/*
* Created by Zeng Yinuo, 2021.09.06
*/

#include "SelectIndexResult.h"

Osmmd::SelectIndexResult::SelectIndexResult()
    : IndexResult()
    , Results(std::make_shared<std::vector<std::shared_ptr<RowValue>>>())
{
}

Osmmd::SelectIndexResult::SelectIndexResult(const SelectIndexResult& other)
    : IndexResult(other)
    , Results(other.Results)
{
}

Osmmd::SelectIndexResult::SelectIndexResult(int row, int col)
    : IndexResult(row, col)
    , Results(std::make_shared<std::vector<std::shared_ptr<RowValue>>>())
{
}

Osmmd::SelectIndexResult::SelectIndexResult(int row, int col, const std::string& message)
    : IndexResult(row, col, message)
    , Results(std::make_shared<std::vector<std::shared_ptr<RowValue>>>())
{
}

Osmmd::SelectIndexResult::SelectIndexResult
(
    int row,
    int col,
    std::shared_ptr<std::vector<std::shared_ptr<RowValue>>> results
)
    : IndexResult(row, col)
    , Results(results)
{
}

Osmmd::SelectIndexResult& Osmmd::SelectIndexResult::operator=(const SelectIndexResult& other)
{
    this->AffectRowCount = other.AffectRowCount;
    this->AffectColCount = other.AffectColCount;
    this->Message = other.Message;
    this->Results = other.Results;

    return *this;
}
