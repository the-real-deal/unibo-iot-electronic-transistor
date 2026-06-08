#include "model/Context.hpp"
#include "model/states/AutomaticState.hpp"
#include "model/states/ManualState.hpp"
#include "model/states/UnconnectedState.hpp"
#include "utils/utility.hpp"
#include "utils/MsgService.hpp"
#include "configs.h"

Context::Context(HWPlatform *platform) : currentState(nullptr), hwPlatform(platform) {}

Context::~Context() {}

void Context::update(Event event)
{
    switch (event)
    {
    case Event::POTENTIOMETER_EVENT:
        int value = map(this->hwPlatform->getPotentiometer()->getValue(), 0, 1024, 0, 90);
        this->hwPlatform->getServoMotor()->setPosition(value);
        MsgService.sendMsg(String(value));
        break;
    case Event::BUTTON_EVENT:
        if (this->currentState->getState() == StateEnum::AUTOMATIC)
        {
            MsgService.sendMsg(MANUAL_STATE);
            setCurrentState(new ManualState(StateEnum::MANUAL));
        }
        else
        {
            MsgService.sendMsg(AUTOMATIC_STATE);
            setCurrentState(new AutomaticState(StateEnum::AUTOMATIC));
        }
        break;
    case Event::MESSAGE_EVENT:
        String msg = MsgService.receiveMsg()->getContent();
        if (isInteger(msg))
        {
            int value = msg.toInt();
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