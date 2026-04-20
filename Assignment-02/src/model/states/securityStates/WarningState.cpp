#include "WarningState.hpp"
#include "DangerState.hpp"
#include "NormalState.hpp"

WarningState::WarningState(HWPlatform *platform, InputHolder *holder) : SecurityState(platform, holder)
{
    this->t = Timer();
}

String WarningState::sendDRUData()
{
    return "Normal";
}

bool WarningState::canReceiveMsg()
{
    return false;
}

void WarningState::initializeTasks() {}

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

String WarningState::getStateInfo()
{
    return "";
}