/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    template<typename T> void SafeDelete(T** pointer)
    {
        if ((*pointer) != nullptr)
        {
            delete (*pointer);
            (*pointer) = nullptr;
        }
    }

    OSMMD_FUNC_API Bytes ReadAllBytesFromFile(std::ifstream& reader);

    OSMMD_FUNC_API void WriteAllBytesToFile(std::ofstream& writer, const Bytes& bytes);
}