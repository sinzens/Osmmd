/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "Global.h"

namespace Osmmd
{
    class OSMMD_CORE_API StringHelper
    {
    public:
        StringHelper();
        StringHelper(const StringHelper& other);
        StringHelper(const char* str);
        StringHelper(const std::string& str);

        bool Contains(char ch) const;
        bool Contains(const std::string& str) const;

        bool StartsWith(const std::string& str) const;
        bool EndsWith(const std::string& str) const;

        StringHelper Left(int count) const;
        StringHelper Right(int count) const;

        StringHelper SubString(int from) const;
        StringHelper SubString(int from, int to) const;

        StringHelper Removed(char ch, bool firstOnly = false) const;
        StringHelper Removed(const std::string& target, bool firstOnly = false) const;

        StringHelper Replaced(const std::string& target, const std::string& replacer, bool firstOnly = false) const;

        StringHelper Trimmed() const;
        StringHelper Densified() const;
        StringHelper Simplified() const;

        StringHelper ToUpperCase() const;
        StringHelper ToLowerCase() const;

        StringHelper ToSqlCompatible() const;

        const std::string& String() const;

        std::vector<std::string> Split(char delim = ' ') const;
        std::vector<std::string> Split(const std::string& delim = " ") const;

        int IndexOf(char ch) const;
        int IndexOf(const std::string& str) const;

        bool operator==(const char* str) const;
        bool operator==(const std::string& str) const;
        bool operator==(const StringHelper& other) const;

    private:
        std::string m_data;
    };
}

