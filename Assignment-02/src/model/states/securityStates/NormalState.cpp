#include "NormalState.hpp"
#include "WarningState.hpp"

NormalState::NormalState(HWPlatform *platform, InputHolder *holder) : SecurityState(platform, holder)
{
    this->t = Timer();
}

String NormalState::sendDRUData()
{
    return "Normal";
}

bool NormalState::canReceiveMsg()
{
    return true;
}

void NormalState::initializeTasks() {}

void NormalState::checkUpdate()
{
    double temp = this->inputHolder->getTemperature();
    if (!this->t.isRunning())
    {
        if (temp > Temp1)
            this->t.init();
    }
    else
    {
        if (temp <= Temp1)
            this->t.reset();
        else if (t.hasExeeded(T3))
        {
            this->context->setSecurityState(new WarningState(this->hwPlatform, this->inputHolder));
        }
    }
}

String NormalState::getStateInfo()
{
    return "";
}