#include "model/Context.hpp"

Context::Context() : currentState(nullptr) {}

Context::~Context() {}

void Context::update(Event event)
{
    switch (event)
    {
    case Event::POTENTIOMETER_EVENT:
        // move servo and send msg with valve level
        break;
    case Event::BUTTON_EVENT:
        // change state
        break;
    case Event::MESSAGE_EVENT:
        // handle message
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
    // subscribe to events / unsubscribe from old ones
    // Likely currentState.updateSubscriptions
}