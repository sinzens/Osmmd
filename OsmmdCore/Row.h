/*
* Created by Zeng Yinuo, 2021.09.01
* Edited by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

#include "Column.h"

namespace Osmmd
{
    struct OSMMD_CORE_API Row : public ISerializable
    {
        std::deque<Column> Columns;

        void AddColumn(const Column& column);

        void RemoveColumn(int index);
        void RemoveColumn(const std::string& name);

        void UpdateColumn(int index, const Column& column);
        void UpdateColumn(const std::string& name, const Column& column);

        const Column& ColumnAt(int index) const;
        const Column& ColumnAt(const std::string& name) const;

        bool HasColumn(const std::string& name) const;
        bool HasColumn(const Column& column) const;

        int ColumnIndex(const std::string& name) const;
        int ColumnIndex(const Column& column) const;

        int GetLength() const;

        Row Sliced(const std::vector<int>& indexes) const;
        Row Sliced(const std::vector<std::string>& columnNames) const;

        std::string ToString() const override;
        Bytes ToBytes() const override;

        static Row FromBytes(const Bytes& bytes);

        bool operator==(const Row& other) const;
        bool operator!=(const Row& other) const;

    private:
        std::map<std::string, int> m_nameIndexMap;
    };
}
