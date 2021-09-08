/*
* Created by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
* Edited by Zeng Yinuo, 2021.09.08
*/

#pragma once

namespace Osmmd
{
    enum class CommandType : unsigned char
    {
        CreateDatabase,
        CreateTable,
        DeleteDatabase,
        DeleteTable,
        Insert,
        Delete,
        Update,
        Select,
        UseDatabase,
        Quit
    };
}
