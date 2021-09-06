/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    struct OSMMD_CORE_API IndexResult
    {
        int AffectRowCount;
        int AffectColCount;

        std::string Message;

        IndexResult();
        IndexResult(const IndexResult& other);
        IndexResult(int row, int col);
        IndexResult(int row, int col, const std::string& message);

        bool IsSuccessful() const;

        IndexResult& operator=(const IndexResult& other);
    };
}
