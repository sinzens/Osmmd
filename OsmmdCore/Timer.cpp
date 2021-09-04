/*
* Created by Zeng Yinuo, 2021.09.04
*/

#include "Timer.h"

static std::mutex durationMutex;

static std::chrono::time_point globalStart = std::chrono::high_resolution_clock::now();
static std::chrono::time_point globalEnd = std::chrono::high_resolution_clock::now();

template<typename T> static double CastDuration
(
    std::chrono::time_point<std::chrono::steady_clock> start,
    std::chrono::time_point<std::chrono::steady_clock> end
)
{
    auto duration = std::chrono::duration_cast<T>(end - start);
    return static_cast<double>(duration.count()) * T::period::num / T::period::den;
}

Osmmd::Timer::Timer()
    : m_start(std::chrono::high_resolution_clock::now())
    , m_end(std::chrono::high_resolution_clock::now())
{
}

void Osmmd::Timer::Start()
{
    m_start = std::chrono::high_resolution_clock::now();
}

void Osmmd::Timer::End()
{
    m_end = std::chrono::high_resolution_clock::now();
}

double Osmmd::Timer::Duration(TimeAccuracy accuracy) const
{
    return GetDuration(m_start, m_end, accuracy);
}

void Osmmd::Timer::GlobalStart()
{
    std::lock_guard<std::mutex> guard(durationMutex);
    globalStart = std::chrono::high_resolution_clock::now();
}

void Osmmd::Timer::GlobalEnd()
{
    std::lock_guard<std::mutex> guard(durationMutex);
    globalEnd = std::chrono::high_resolution_clock::now();
}

double Osmmd::Timer::GlobalDuration(TimeAccuracy accuracy)
{
    return GetDuration(globalStart, globalEnd, accuracy);
}

double Osmmd::Timer::GetDuration(
    std::chrono::time_point<std::chrono::steady_clock> start,
    std::chrono::time_point<std::chrono::steady_clock> end,
    TimeAccuracy accuracy
)
{
    double durationValue = 0;

    switch (accuracy)
    {
    case TimeAccuracy::Hour:
        durationValue = CastDuration<std::chrono::hours>(start, end) / 3600;
        break;
    case TimeAccuracy::Minute:
        durationValue = CastDuration<std::chrono::minutes>(start, end) / 60;
        break;
    case TimeAccuracy::Second:
        durationValue = CastDuration<std::chrono::seconds>(start, end);
        break;
    case TimeAccuracy::Millisecond:
        durationValue = CastDuration<std::chrono::milliseconds>(start, end) * 1000;
        break;
    case TimeAccuracy::Microsecond:
        durationValue = CastDuration<std::chrono::microseconds>(start, end) * 1000000;
        break;
    case TimeAccuracy::Nanosecond:
        durationValue = CastDuration<std::chrono::nanoseconds>(start, end) * 1000000000;
        break;
    }

    return durationValue;
}
