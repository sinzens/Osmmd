/*
* Created by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "IndexResult.h"
#include "RowValue.h"

namespace Osmmd
{
    struct OSMMD_CORE_API SelectIndexResult : public IndexResult
    {
        std::shared_ptr<std::vector<std::shared_ptr<RowValue>>> Results;

        SelectIndexResult();

        SelectIndexResult(const SelectIndexResult& other);

        SelectIndexResult(int row, int col);
        SelectIndexResult(int row, int col, const std::string& message);

        SelectIndexResult
        (
            int row,
            int col,
            std::shared_ptr<std::vector<std::shared_ptr<RowValue>>> results
        );

        SelectIndexResult& operator=(const SelectIndexResult& other);
    };
}
