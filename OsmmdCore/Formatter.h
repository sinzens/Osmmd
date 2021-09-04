/*
* Created by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
*/

#pragma once

#include "ISerializable.h"
#include "StringHelper.h"
#include "Type.h"

namespace Osmmd
{
    class OSMMD_CORE_API Formatter
    {
    public:
        template<typename ...Args>
        static std::string Format(const Args &... args);

        template<typename ...Args>
        static std::string Format(const char* format, const Args &... args);

    private:
        template<typename T, typename ...Args>
        static std::string FormatWithDefault(const T& arg, const Args &... args);

        template<typename T, typename ...Args>
        static std::string FormatWithFormatter(const char* formatter, const T& arg, const Args &... args);

        template<typename T>
        static std::string FormatSingle(const T& arg);
    };

    template<typename ...Args>
    inline std::string Formatter::Format(const Args &... args)
    {
        if constexpr (sizeof...(Args) == 0)
        {
            return std::string();
        }
        else
        {
            return Formatter::FormatWithDefault(args...);
        }
    }

    template<typename ...Args>
    inline std::string Formatter::Format(const char* format, const Args &... args)
    {
        if constexpr (sizeof...(Args) == 0)
        {
            return std::string(format);
        }
        else
        {
            return Formatter::FormatWithFormatter(format, args...);
        }
    }

    template<typename T, typename ...Args>
    inline std::string Formatter::FormatWithDefault(const T& arg, const Args &... args)
    {
        std::string current = Formatter::FormatSingle(arg);
        if constexpr (sizeof...(Args) == 0)
        {
            return current;
        }
        else
        {
            return current + ", " + Formatter::FormatWithDefault(args...);
        }
    }

    template<typename T, typename ...Args>
    inline std::string Formatter::FormatWithFormatter(const char* format, const T& arg, const Args &... args)
    {
        std::string current = Formatter::FormatSingle(arg);
        std::string currentFormatter = StringHelper(format).Replaced("{}", current, true).GetString();

        if constexpr (sizeof...(Args) == 0)
        {
            return currentFormatter;
        }
        else
        {
            return Formatter::FormatWithFormatter(currentFormatter.c_str(), args...);
        }
    }

    template<typename T>
    inline std::string Formatter::FormatSingle(const T& arg)
    {
        try
        {
            if constexpr (IsDerivedClass<T, ISerializable>())
            {
                return arg.ToString();
            }
            else if constexpr (IsSameType<T, bool>())
            {
                return std::string(arg ? "true" : "false");
            }
            else
            {
                return std::string((std::stringstream() << arg).str());
            }
        }
        catch (const std::exception& e)
        {
            return std::string("Unsupported");
        }
    }
}
