/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    template<typename T, typename ...Args>
    constexpr auto Min(const T& arg, const Args &... args)
    {
        if constexpr (sizeof...(Args) == 0)
        {
            return arg;
        }
        else
        {
            const auto result = Min(args...);
            return arg < result ? arg : result;
        }
    }

    template<typename T, typename ...Args>
    constexpr auto Max(const T& arg, const Args &... args)
    {
        if constexpr (sizeof...(Args) == 0)
        {
            return arg;
        } else
        {
            const auto result = Min(args...);
            return arg > result ? arg : result;
        }
    }

    template<typename T>
    constexpr auto Bound(const T& min, const T& value, const T& max)
    {
        return Max(min, Min(value, max));
    }

    template<typename ...Args>
    constexpr auto Sum(const Args &... arg)
    {
        return (... + arg);
    }

    template<typename ...Args>
    constexpr auto Multiply(const Args &... arg)
    {
        return (... * arg);
    }

    template<typename T>
    constexpr uint8_t GetByte(const T& value, int index)
    {
        return value >> (8 * index) & 0xFF;
    }

    OSMMD_FUNC_API std::string GetHex(unsigned int number);
}