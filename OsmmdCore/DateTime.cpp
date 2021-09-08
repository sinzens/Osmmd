/*
* Created by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "DateTime.h"

Osmmd::DateTime::DateTime()
{
    time_t now = time(0);
    tm localTime;

    localtime_s(&localTime, &now);

    this->Year = 1900 + localTime.tm_year;
    this->Month = 1 + localTime.tm_mon;
    this->Day = localTime.tm_mday;

    this->Hour = localTime.tm_hour;
    this->Minute = localTime.tm_min;
    this->Second = localTime.tm_sec;
}

Osmmd::DateTime::DateTime(const DateTime& other)
    : Year(other.Year)
    , Month(other.Month)
    , Day(other.Day)
    , Hour(other.Hour)
    , Minute(other.Minute)
    , Second(other.Second)
{
}

Osmmd::DateTime::DateTime(int16_t year, int8_t month, int8_t day, int8_t hour, int8_t minute, int8_t second)
    : Year(year)
    , Month(month)
    , Day(day)
    , Hour(hour)
    , Minute(minute)
    , Second(second)
{
    this->Validate();
}

std::string Osmmd::DateTime::ToString() const
{
    char buffer[50]{};
    sprintf_s(buffer, "%04d-%02d-%02d %02d:%02d:%02d", this->Year, this->Month, this->Day, this->Hour, this->Minute, this->Second);

    return buffer;
}

Bytes Osmmd::DateTime::ToBytes() const
{
    unsigned char data[sizeof(int16_t) + 5 * sizeof(int8_t)]{};

    int16_t value = this->Year;

    data[0] = value;
    data[1] = value >> 8;
    data[2] = static_cast<unsigned char>(this->Month);
    data[3] = static_cast<unsigned char>(this->Day);
    data[4] = static_cast<unsigned char>(this->Hour);
    data[5] = static_cast<unsigned char>(this->Minute);
    data[6] = static_cast<unsigned char>(this->Second);

    return Bytes(data, data + sizeof(data));
}

int Osmmd::DateTime::Compare(const DateTime& other) const
{
    if (this->Year < other.Year)
    {
        return -1;
    }

    if (this->Year > other.Year)
    {
        return 1;
    }

    if (this->Month < other.Month)
    {
        return -1;
    }

    if (this->Month > other.Month)
    {
        return 1;
    }

    if (this->Day < other.Day)
    {
        return -1;
    }

    if (this->Day > other.Day)
    {
        return 1;
    }

    if (this->Hour < other.Hour)
    {
        return -1;
    }

    if (this->Hour > other.Hour)
    {
        return 1;
    }

    if (this->Minute < other.Minute)
    {
        return -1;
    }

    if (this->Minute > other.Minute)
    {
        return 1;
    }

    if (this->Second < other.Second)
    {
        return -1;
    }

    if (this->Second > other.Second)
    {
        return 1;
    }

    return 0;
}

Osmmd::DateTime Osmmd::DateTime::FromBytes(const Bytes& bytes)
{
    int16_t number = bytes.at(0) & 0xFF;
    number |= ((bytes.at(1) << 8) & 0xFF00);

    return DateTime
    (
        number,
        static_cast<int8_t>(bytes.at(2)),
        static_cast<int8_t>(bytes.at(3)),
        static_cast<int8_t>(bytes.at(4)),
        static_cast<int8_t>(bytes.at(5)),
        static_cast<int8_t>(bytes.at(6))
    );
}

Osmmd::DateTime Osmmd::DateTime::FromString(const std::string& str)
{
    int year, month, day, hour, minute, second;

    int successful = sscanf_s
    (
        str.c_str(),
        "%d-%d-%d %d:%d:%d",
        &year,
        &month,
        &day,
        &hour,
        &minute,
        &second
    );

    return successful == 6
        ? DateTime(year, month, day, hour, minute, second)
        : DateTime();
}

Osmmd::DateTime& Osmmd::DateTime::operator=(const DateTime& other)
{
    this->Year = other.Year;
    this->Month = other.Month;
    this->Day = other.Day;

    this->Hour = other.Hour;
    this->Minute = other.Minute;
    this->Second = other.Second;

    return *this;
}

void Osmmd::DateTime::Validate()
{
    if (this->Year < 1900 || this->Year > 2099)
    {
        this->Year = 1900;
    }

    if (this->Month < 1 || this->Month > 12)
    {
        this->Month = 1;
    }

    if (this->Day < 1 || this->Day > 31)
    {
        this->Day = 1;
    }

    if (this->Hour < 0 || this->Hour > 23)
    {
        this->Hour = 0;
    }

    if (this->Minute < 0 || this->Minute > 59)
    {
        this->Minute = 0;
    }

    if (this->Second < 0 || this->Second > 59)
    {
        this->Second = 0;
    }
}
