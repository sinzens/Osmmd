/*
* Created by Zeng Yinuo, 2021.09.04
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    template<typename T>
    class OSMMD_CORE_API IComparable
    {
        friend bool operator<(const T& a, const T& b) { return a.Compare(b) < 0; }
        friend bool operator<=(const T& a, const T& b) { return a.Compare(b) <= 0; }
        friend bool operator>(const T& a, const T& b) { return a.Compare(b) > 0; }
        friend bool operator>=(const T& a, const T& b) { return a.Compare(b) >= 0; }
        friend bool operator==(const T& a, const T& b) { return a.Compare(b) == 0; }
        friend bool operator!=(const T& a, const T& b) { return a.Compare(b) != 0; }

    public:
        virtual int Compare(const T& other) const = 0;
    };
}
