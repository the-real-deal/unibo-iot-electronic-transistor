#include "model/Context.hpp"
#include "model/states/AutomaticState.hpp"
#include "model/states/ManualState.hpp"
#include "model/states/UnconnectedState.hpp"
#include "utils/utility.hpp"
#include "utils/MsgService.hpp"
#include "configs.h"
#include "Context.hpp"
#include "events/EventManager.hpp"

Context::Context() : currentState(nullptr), hwPlatform(nullptr) {}

Context::~Context() {}

void Context::update(Event event)
{
    String msg;
    int value;

    switch (event)
    {
    case Event::BUTTON_EVENT:
        if (this->currentState->getState() == StateEnum::AUTOMATIC)
        {
            MsgService.sendMsg(MANUAL_STATE);
            setCurrentState(new ManualState(StateEnum::MANUAL));
        }
        else if (this->currentState->getState() == StateEnum::MANUAL)
        {
            MsgService.sendMsg(AUTOMATIC_STATE);
            setCurrentState(new AutomaticState(StateEnum::AUTOMATIC));
        }
        break;
    case Event::POTENTIOMETER_EVENT:
        value = this->hwPlatform->getPotentiometer()->getValue(); // map(this->hwPlatform->getPotentiometer()->getValue(), 0, 1024, 0, 90);
        this->hwPlatform->getServoMotor()->setPosition(map(value, 0, 1024, 0, 90));
        MsgService.sendMsg(String(map(value, 0, 1024, 0, 100)));
        break;

    case Event::MESSAGE_EVENT:
        msg = MsgService.receiveMsg()->getContent();
        if (isInteger(msg))
        {
            int value = map(msg.toInt(), 0, 100, 0, 90);
            this->hwPlatform->getServoMotor()->setPosition(value);
        }
        else
        {
            if (msg == AUTOMATIC_STATE)
            {
                setCurrentState(new AutomaticState(StateEnum::AUTOMATIC));
            }
            else if (msg == MANUAL_STATE)
            {
                setCurrentState(new ManualState(StateEnum::MANUAL));
            }
            else if (msg == UNCONNECTED_STATE)
            {
                setCurrentState(new UnconnectedState(StateEnum::UNCONNECTED));
            }
        }
        break;
    }
}

void Context::setCurrentState(State *state)
{
    if (this->currentState != nullptr)
    {
        delete this->currentState;
    }
    this->currentState = state;
    this->hwPlatform->getLCD()->print(this->currentState->getValue());
    this->currentState->manageEvents();
}

void Context::setHwPlatform(HWPlatform *plt)
{
    if (this->hwPlatform == nullptr)
    {
        this->hwPlatform = plt;
    }
}