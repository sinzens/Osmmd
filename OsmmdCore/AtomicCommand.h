/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
*/

#pragma once

#include "IExecutable.h"

namespace Osmmd
{
    class OSMMD_CORE_API AtomicCommand : public IExecutable
    {
    public:
        virtual std::shared_ptr<CommandResult> Execute() override;

        CommandType GetType() const;

    protected:
        virtual std::shared_ptr<CommandResult> DoExecute() = 0;

        CommandType m_type = CommandType::Select;
    };
}


