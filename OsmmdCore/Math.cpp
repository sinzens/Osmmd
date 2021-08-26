/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.08.26
*/

#include "Math.h"

static constexpr const char HEX_CHARS[] =
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};

std::string Osmmd::GetHex(unsigned int number)
{
    std::string result;

    unsigned char* temp = reinterpret_cast<unsigned char*>(&number);
    constexpr int length = sizeof(number);

    for (int i = 0; i < length; i++)
    {
        unsigned char ch = temp[i] & 0xF0;
        ch >>= 4;
        result.append(1, HEX_CHARS[ch]);
        ch = temp[i] & 0x0F;
        result.append(1, HEX_CHARS[ch]);
    }

    return result;
}
