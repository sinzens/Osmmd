/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "Global.h"
#include "DataType.h"
#include "IndexStrategy.h"
#include "CommandType.h"
#include "ConditionOperator.h"

namespace Osmmd
{
    OSMMD_FUNC_API std::string GetDataTypeName(DataType type);
    OSMMD_FUNC_API DataType GetDataType(const std::string& name);
    OSMMD_FUNC_API bool IsKnownDataType(const std::string& name);

    OSMMD_FUNC_API std::string GetIndexStrategyName(IndexStrategy indexStrategy);
    OSMMD_FUNC_API IndexStrategy GetIndexStrategy(const std::string& name);
    OSMMD_FUNC_API bool IsKnownIndexStrategy(const std::string& name);

    OSMMD_FUNC_API std::string GetCommandTypeName(CommandType type);
    OSMMD_FUNC_API CommandType GetCommandType(const std::string& name);

    OSMMD_FUNC_API std::string GetConditionOperatorName(ConditionOperator opt);
    OSMMD_FUNC_API ConditionOperator GetConditionOperator(const std::string& name);
    OSMMD_FUNC_API bool IsKnownConditionOperator(const std::string& name);
    OSMMD_FUNC_API ConditionOperator GetInvertedConditionOperator(ConditionOperator opt);
    OSMMD_FUNC_API ConditionOperator GetOppositeConditionOperator(ConditionOperator opt);
}
