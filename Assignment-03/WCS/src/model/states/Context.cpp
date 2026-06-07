#include "model/states/Context.hpp"

Context::Context() : currentState(nullptr) {}

Context::~Context() {}

void Context::update(Event event) {}

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