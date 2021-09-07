/*
* Created by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "ISerializable.h"
#include "IComparable.h"

namespace Osmmd
{
    struct OSMMD_CORE_API DateTime : public ISerializable, public IComparable<DateTime>
    {
        int16_t Year;
        int8_t Month;
        int8_t Day;

        int8_t Hour;
        int8_t Minute;
        int8_t Second;

        DateTime();

        DateTime(const DateTime& other);

        DateTime
        (
            int16_t year,
            int8_t month,
            int8_t day,
            int8_t hour,
            int8_t minute,
            int8_t second
        );

        std::string ToString() const override;
        Bytes ToBytes() const override;

        int Compare(const DateTime& other) const override;

        static DateTime FromBytes(const Bytes& bytes);
        static DateTime FromString(const std::string& str);

        DateTime& operator=(const DateTime& other);

    private:
        void Validate();
    };
}
