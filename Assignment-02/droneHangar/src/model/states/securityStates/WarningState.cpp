#include "WarningState.hpp"
#include "DangerState.hpp"
#include "NormalState.hpp"
#include "model/messageManager/MsgService.h"

WarningState::WarningState(HWPlatform *platform, InputHolder *holder) : SecurityState(platform, holder), t(Timer())
{
}

bool WarningState::canReceiveMsg()
{
    return false;
}

void WarningState::initializeTasks()
{
    MsgService.sendMsg(WARNING_STATE_MESSAGE);
}

void WarningState::checkUpdate()
{
    double temp = this->inputHolder->getTemperature();
    if (!this->t.isRunning())
    {
        if (temp > Temp2)
            this->t.init();
    }
    else
    {
        if (temp <= Temp2)
            this->t.reset();
        else if (temp <= Temp1)
            this->context->setSecurityState(new NormalState(this->hwPlatform, this->inputHolder));
        else if (t.hasExeeded(T3))
        {
            this->context->setSecurityState(new DangerState(this->hwPlatform, this->inputHolder));
        }
    }
}
