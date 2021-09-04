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
        Timer();

        void Start();
        void End();
        
        double Duration(TimeAccuracy accuracy = TimeAccuracy::Millisecond) const;

        static void GlobalStart();
        static void GlobalEnd();

        static double GlobalDuration(TimeAccuracy accuracy = TimeAccuracy::Millisecond);

    private:
        static double GetDuration
        (
            std::chrono::time_point<std::chrono::steady_clock> start,
            std::chrono::time_point<std::chrono::steady_clock> end,
            TimeAccuracy accuracy
        );

        std::chrono::time_point<std::chrono::steady_clock> m_start;
        std::chrono::time_point<std::chrono::steady_clock> m_end;
    };
}
