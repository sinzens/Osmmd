/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
* Edited by Zeng Yinuo, 2021.09.06
*/

#pragma once

#include "Value.h"
#include "IndexStrategy.h"
#include "ConditionOperator.h"

namespace Osmmd
{
    class OSMMD_CORE_API Random
    {
    public:
        static int32_t RandomInteger(int32_t min = 0, int32_t max = INT_MAX, int seed = -1);

        static std::string RandomString(int length, int seed = -1);

        static DataType RandomDataType(int seed = -1);
        static IndexStrategy RandomIndexStrategy(int seed = -1);
        static ConditionOperator RandomConditionOperator(int seed = -1);

        static Value RandomValue(int seed = -1);
        static Value RandomValue(DataType type, int seed = -1);
    };
}
