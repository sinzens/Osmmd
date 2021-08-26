/*
* Created by Zeng Yinuo, 2021.08.26
*/

#include "PerformanceConfiguration.h"

std::string Osmmd::PerformanceConfiguration::ToBytes() const
{
    return std::string();
}

Osmmd::PerformanceConfiguration Osmmd::PerformanceConfiguration::FromBytes(const std::string& bytes)
{
    return PerformanceConfiguration();
}

Osmmd::PerformanceConfiguration& Osmmd::PerformanceConfiguration::operator=(const PerformanceConfiguration& other)
{
    this->TIMING = other.TIMING;
    return *this;
}
