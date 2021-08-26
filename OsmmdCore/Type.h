/*
* Created by Zeng Yinuo, 2021.08.26
*/

#include "Global.h"

#pragma once

namespace Osmmd
{
    template<typename T1, typename T2>
    constexpr bool IsSameType()
    {
        return std::is_same_v<typename std::decay<T1>::type, typename std::decay<T2>::type>;
    }

    template<typename T1, typename T2>
    constexpr bool IsExactlySameType()
    {
        return std::is_same_v<T1, T2>;
    }

    template<typename T1, typename T2>
    constexpr bool IsBaseClass()
    {
        return std::is_base_of_v<T1, T2>;
    }

    template<typename T1, typename T2>
    constexpr bool IsDerivedClass()
    {
        return std::is_base_of_v<T2, T1>;
    }
}
