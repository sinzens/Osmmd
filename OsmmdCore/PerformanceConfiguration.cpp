/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
*/

#include "PerformanceConfiguration.h"

std::string Osmmd::PerformanceConfiguration::ToString() const
{
    return std::string();
}

Bytes Osmmd::PerformanceConfiguration::ToBytes() const
{
    return Bytes();
}

Osmmd::PerformanceConfiguration Osmmd::PerformanceConfiguration::FromBytes(const Bytes & bytes)
{
    return PerformanceConfiguration();
}

Osmmd::PerformanceConfiguration& Osmmd::PerformanceConfiguration::operator=(const PerformanceConfiguration& other)
{
    this->TIMING = other.TIMING;
    return *this;
}
