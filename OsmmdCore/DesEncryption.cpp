/*
* Created by Zeng Yinuo, 2021.08.26
*/

#include "DesEncryption.h"

constexpr const char KEYS[8] = { 0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF };

std::string Osmmd::DesEncryption::Encode(const std::string& bytes) const
{
    return bytes;
}

std::string Osmmd::DesEncryption::Decode(const std::string& bytes) const
{
    return bytes;
}
