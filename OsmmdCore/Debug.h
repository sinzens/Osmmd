/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "Formatter.h"

namespace Osmmd
{
    class OSMMD_CORE_API Debug
    {
    public:
        template<typename ...Args>
        static void Write(const Args &... args);

        template<typename ...Args>
        static void Write(const char* format, const Args &... args);

        template<typename ...Args>
        static void WriteLine(const Args &... args);

        template<typename ...Args>
        static void WriteLine(const char* format, const Args &... args);

        template<typename ...Args>
        static void Error(const Args &... args);

        template<typename ...Args>
        static void Error(const char* format, const Args &... args);

        template<typename ...Args>
        static void ErrorLine(const Args &... args);

        template<typename ...Args>
        static void ErrorLine(const char* format, const Args &... args);
    };

    template<typename ...Args>
    inline void Debug::Write(const Args & ...args)
    {
        std::cout << Formatter::Format(args...);
    }

    template<typename ...Args>
    inline void Debug::Write(const char* format, const Args & ...args)
    {
        std::cout << Formatter::Format(format, args...);
    }

    template<typename ...Args>
    inline void Debug::WriteLine(const Args & ...args)
    {
        std::cout << Formatter::Format(args...) << std::endl;
    }

    template<typename ...Args>
    inline void Debug::WriteLine(const char* format, const Args & ...args)
    {
        std::cout << Formatter::Format(format, args...) << std::endl;
    }

    template<typename ...Args>
    inline void Debug::Error(const Args & ...args)
    {
        std::cerr << Formatter::Format(args...);
    }

    template<typename ...Args>
    inline void Debug::Error(const char* format, const Args & ...args)
    {
        std::cerr << Formatter::Format(format, args...);
    }

    template<typename ...Args>
    inline void Debug::ErrorLine(const Args & ...args)
    {
        std::cerr << Formatter::Format(args...) << std::endl;
    }

    template<typename ...Args>
    inline void Debug::ErrorLine(const char* format, const Args & ...args)
    {
        std::cerr << Formatter::Format(format, args...) << std::endl;
    }
}
