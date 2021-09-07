/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.09.06
* Edited by Zeng Yinuo, 2021.09.07
*/

#include "AtomicCommand.h"
#include "Driver.h"
#include "Timer.h"

std::shared_ptr<Osmmd::CommandResult> Osmmd::AtomicCommand::Execute()
{
    if (TIMING_ON)
    {
        Timer timer;
        timer.Start();

        std::shared_ptr<CommandResult> result = this->DoExecute();

        timer.End();
        result->TimeElapse = timer.Duration(TimeAccuracy::Millisecond);

        return result;
    }
    
    return this->DoExecute();
}

Osmmd::CommandType Osmmd::AtomicCommand::GetType() const
{
    return m_type;
}
