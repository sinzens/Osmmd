/*
* Created by Zeng Yinuo, 2021.08.23
*/

#pragma once

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
}