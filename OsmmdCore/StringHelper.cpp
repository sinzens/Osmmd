/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.08.26
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "StringHelper.h"

Osmmd::StringHelper::StringHelper()
{
}

Osmmd::StringHelper::StringHelper(const StringHelper& other)
    : m_data(other.m_data)
{
}

Osmmd::StringHelper::StringHelper(const char* str)
    : m_data(str)
{
}

Osmmd::StringHelper::StringHelper(const std::string& str)
    : m_data(str)
{
}

bool Osmmd::StringHelper::Contains(char ch) const
{
    return m_data.find(ch) != std::string::npos;
}

bool Osmmd::StringHelper::Contains(const std::string& str) const
{
    return m_data.find(str) != std::string::npos;
}

bool Osmmd::StringHelper::StartsWith(const std::string& str) const
{
    return this->Left(str.length()) == str;
}

bool Osmmd::StringHelper::EndsWith(const std::string& str) const
{
    return this->Right(str.length()) == str;
}

bool Osmmd::StringHelper::IsValidIdentifier() const
{
    return this->GetLength() >= 2 && this->ContainsOnlyLettersNumbersAndUnderscore() && !this->StartsWithNumber();
}

bool Osmmd::StringHelper::StartsWithNumber() const
{
    if (m_data.empty())
    {
        return false;
    }

    char front = m_data.front();

    return '0' <= front && front <= '9';
}

bool Osmmd::StringHelper::ContainsOnlyNumbers() const
{
    if (m_data.empty())
    {
        return false;
    }

    for (char ch : m_data)
    {
        if (ch < '0' || ch > '9')
        {
            return false;
        }
    }

    return true;
}

bool Osmmd::StringHelper::ContainsOnlyLettersAndNumbers() const
{
    if (m_data.empty())
    {
        return false;
    }

    for (char ch : m_data)
    {
        bool isLetter = ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z');
        bool isNumber = '0' <= ch && ch <= '9';

        if (!isLetter && !isNumber)
        {
            return false;
        }
    }

    return true;
}

bool Osmmd::StringHelper::ContainsOnlyLettersNumbersAndUnderscore() const
{
    if (m_data.empty())
    {
        return false;
    }

    for (char ch : m_data)
    {
        bool isLetter = ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z');
        bool isNumber = ('0' <= ch && ch <= '9');
        bool isUnderscore = (ch == '_');

        if (!isLetter && !isNumber && !isUnderscore)
        {
            return false;
        }
    }

    return true;
}

bool Osmmd::StringHelper::IsDouble(bool strict) const
{
    if (m_data.empty())
    {
        return false;
    }

    if (strict && !this->Contains("."))
    {
        return false;
    }

    for (char ch : m_data)
    {
        if ((ch < '0' || ch > '9') && ch != '.')
        {
            return false;
        }
    }

    return true;
}

Osmmd::StringHelper Osmmd::StringHelper::Left(int count) const
{
    return StringHelper(count <= m_data.length() ? m_data.substr(0, count) : m_data);
}

Osmmd::StringHelper Osmmd::StringHelper::Right(int count) const
{
    return StringHelper
    (
        count <= m_data.length()
        ? m_data.substr(m_data.length() - count, count)
        : m_data
    );
}

Osmmd::StringHelper Osmmd::StringHelper::SubString(int from) const
{
    return this->SubString(from, m_data.length());
}

Osmmd::StringHelper Osmmd::StringHelper::SubString(int from, int to) const
{
    return StringHelper
    (
        (from >= 0 && from < m_data.length())
        ? m_data.substr(from, to - from)
        : m_data
    );
}

Osmmd::StringHelper Osmmd::StringHelper::Removed(char ch, bool firstOnly) const
{
    return this->Removed(std::string(1, ch), firstOnly);
}

Osmmd::StringHelper Osmmd::StringHelper::Removed(const std::string& target, bool firstOnly) const
{
    std::string result = m_data;

    size_t pos = result.find(target);
    if (firstOnly)
    {
        if (pos != std::string::npos)
        {
            result.erase(pos, target.length());
        }
    }
    else
    {
        while (pos != std::string::npos)
        {
            result.erase(pos, target.length());
            pos = result.find(target);
        }
    }

    return StringHelper(result);
}

Osmmd::StringHelper Osmmd::StringHelper::Replaced(const std::string& target, const std::string& replacer, bool firstOnly) const
{
    std::string result = m_data;

    size_t pos = result.find(target);
    if (firstOnly)
    {
        if (pos != std::string::npos)
        {
            result.replace(pos, target.length(), replacer);
        }
    }
    else
    {
        while (pos != std::string::npos)
        {
            result.replace(pos, target.length(), replacer);
            pos = result.find(target);
        }
    }

    return StringHelper(result);
}

Osmmd::StringHelper Osmmd::StringHelper::Trimmed() const
{
    std::string result = m_data;

    result.erase(0, result.find_first_not_of(" "));
    result.erase(result.find_last_not_of(" ") + 1);

    return StringHelper(result);
}

Osmmd::StringHelper Osmmd::StringHelper::Densified() const
{
    return this->Removed(' ');
}

Osmmd::StringHelper Osmmd::StringHelper::Simplified() const
{
    size_t counter = 0;
    bool isStart = false;

    std::string result = m_data;

    for (size_t i = 0; i < result.length(); i++)
    {
        if (result.at(i) == ' ' || result.at(i) == '\n' || result.at(i) == '\r')
        {
            counter++;
            if (i == 0) { isStart = true; }
            if (i == result.length() - 1)
            {
                size_t offset = i - counter + 1;
                size_t count = counter;
                result.erase(offset, count);
            }
        }
        else
        {
            if (counter > 0)
            {
                size_t offset = i - counter;
                size_t count = isStart ? counter : counter - 1;
                result.erase(offset, count);
                if (isStart) { isStart = false; }
                i -= count;
                counter = 0;
            }
        }
    }

    return StringHelper(result);
}

Osmmd::StringHelper Osmmd::StringHelper::ToUpperCase() const
{
    std::string result = m_data;
    std::transform(m_data.begin(), m_data.end(), result.begin(), toupper);
    return StringHelper(result);
}

Osmmd::StringHelper Osmmd::StringHelper::ToLowerCase() const
{
    std::string result = m_data;
    std::transform(m_data.begin(), m_data.end(), result.begin(), tolower);
    return StringHelper(result);
}

Osmmd::StringHelper Osmmd::StringHelper::ToSqlCompatible() const
{
    return this->Simplified().ToLowerCase();
}

int Osmmd::StringHelper::GetLength() const
{
    return m_data.size();
}

const std::string& Osmmd::StringHelper::GetString() const
{
    return m_data;
}

std::vector<std::string> Osmmd::StringHelper::Split(char delim) const
{
    return this->Split(std::string(1, delim));
}

std::vector<std::string> Osmmd::StringHelper::Split(const std::string& delim) const
{
    std::vector<std::string> strs;

    if (delim.size() == 1)
    {
        size_t lastPos = m_data.find_first_not_of(delim, 0);
        size_t pos = m_data.find_first_of(delim, lastPos);

        while (std::string::npos != pos || std::string::npos != lastPos)
        {
            strs.emplace_back(m_data.substr(lastPos, pos - lastPos));
            lastPos = m_data.find_first_not_of(delim, pos);
            pos = m_data.find_first_of(delim, lastPos);
        }

        return strs;
    }

    size_t pos1 = 0;
    size_t pos2 = m_data.find(delim);

    while (std::string::npos != pos2)
    {
        strs.emplace_back(m_data.substr(pos1, pos2 - pos1));

        pos1 = pos2 + delim.size();
        pos2 = m_data.find(delim, pos1);
    }

    if (pos1 != m_data.length())
    {
        strs.emplace_back(m_data.substr(pos1));
    }
    
    return strs;
}

int Osmmd::StringHelper::IndexOf(char ch) const
{
    return this->IndexOf(std::string(1, ch));
}

int Osmmd::StringHelper::IndexOf(const std::string& str) const
{
    return m_data.find(str);
}

int Osmmd::StringHelper::Compare(const StringHelper& other) const
{
    return m_data.compare(other.m_data);
}

bool Osmmd::StringHelper::operator==(const char* str) const
{
    return m_data == str;
}

bool Osmmd::StringHelper::operator==(const std::string& str) const
{
    return m_data == str;
}

bool Osmmd::StringHelper::operator==(const StringHelper& other) const
{
    return m_data == other.m_data;
}

bool Osmmd::StringHelper::operator!=(const char* str) const
{
    return m_data != str;
}

bool Osmmd::StringHelper::operator!=(const std::string& str) const
{
    return m_data != str;
}

bool Osmmd::StringHelper::operator!=(const StringHelper& other) const
{
    return m_data != other.m_data;
}
