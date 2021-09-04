/*
* Created by Zeng Yinuo, 2021.09.04
*/

#include "Timer.h"

static std::chrono::time_point start = std::chrono::high_resolution_clock::now();
static std::chrono::time_point end = std::chrono::high_resolution_clock::now();

template<typename T> static double CastDuration()
{
    auto duration = std::chrono::duration_cast<T>(end - start);
    return static_cast<double>(duration.count()) * T::period::num / T::period::den;
}

void Osmmd::Timer::Start()
{
    start = std::chrono::high_resolution_clock::now();
}

void Osmmd::Timer::End()
{
    end = std::chrono::high_resolution_clock::now();
}

double Osmmd::Timer::Duration(TimeAccuracy accuracy)
{
    double durationValue = 0;

    switch (accuracy)
    {
    case TimeAccuracy::Hour:
        durationValue = CastDuration<std::chrono::hours>() / 3600;
        break;
    case TimeAccuracy::Minute:
        durationValue = CastDuration<std::chrono::minutes>() / 60;
        break;
    case TimeAccuracy::Second:
        durationValue = CastDuration<std::chrono::seconds>();
        break;
    case TimeAccuracy::Millisecond:
        durationValue = CastDuration<std::chrono::milliseconds>() * 1000;
        break;
    case TimeAccuracy::Microsecond:
        durationValue = CastDuration<std::chrono::microseconds>() * 1000000;
        break;
    case TimeAccuracy::Nanosecond:
        durationValue = CastDuration<std::chrono::nanoseconds>() * 1000000000;
        break;
    }

    return durationValue;
}
