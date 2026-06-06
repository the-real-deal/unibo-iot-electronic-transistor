#pragma once
#include "model/states/State.hpp"
#include "events/Event.hpp"

class Context
{
public:
    Context();
    ~Context();

    /*
     * Changes the current state, method called by the states themselves
     */
    void setCurrentState(State *state);

    /**
     * Handles the given event
     * @param event the event to handle
     */
    void handleEvent(Event *event);

private:
    State *currentState;
};
