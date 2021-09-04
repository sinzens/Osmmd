/*
* Created by Zeng Yinuo, 2021.09.04
*/

#pragma once

#include "Global.h"
#include "TimeAccuracy.h"

namespace Osmmd
{
    class OSMMD_CORE_API Timer
    {
    public:
        static void Start();
        static void End();

        static double Duration(TimeAccuracy accuracy = TimeAccuracy::Millisecond);
    };
}
