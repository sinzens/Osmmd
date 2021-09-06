/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "Global.h"
#include "DataType.h"
#include "IndexStrategy.h"
#include "CommandType.h"

namespace Osmmd
{
    OSMMD_FUNC_API std::string GetDataTypeName(DataType type);
    OSMMD_FUNC_API DataType GetDataType(const std::string& name);

    OSMMD_FUNC_API std::string GetIndexStrategyName(IndexStrategy indexStrategy);
    OSMMD_FUNC_API IndexStrategy GetIndexStrategy(const std::string& name);

    OSMMD_FUNC_API std::string GetCommandTypeName(CommandType type);
    OSMMD_FUNC_API CommandType GetCommandType(const std::string& name);
}
