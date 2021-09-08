/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "IndexResult.h"

Osmmd::IndexResult::IndexResult()
    : AffectRowCount(0)
    , AffectColCount(0)
{
}

Osmmd::IndexResult::IndexResult(const IndexResult& other)
    : AffectRowCount(other.AffectRowCount)
    , AffectColCount(other.AffectColCount)
    , Message(other.Message)
{
}

Osmmd::IndexResult::IndexResult(int row, int col)
    : AffectRowCount(row)
    , AffectColCount(col)
{
}

Osmmd::IndexResult::IndexResult(int row, int col, const std::string& message)
    : AffectRowCount(row)
    , AffectColCount(col)
    , Message(message)
{
}

bool Osmmd::IndexResult::IsSuccessful() const
{
    return this->Message.empty();
}

Osmmd::IndexResult& Osmmd::IndexResult::operator=(const IndexResult& other)
{
    this->AffectRowCount = other.AffectRowCount;
    this->AffectColCount = other.AffectColCount;
    this->Message = other.Message;

    return *this;
}
