#pragma once
#include "configs.h"
enum StateEnum
{
    MANUAL,
    AUTOMATIC,
    UNCONNECTED
};

class State
{

public:
    State(StateEnum state)
    {
        this->state = state;
    }
    virtual ~State() = default;

    /**
     * Unsubscribes the handler from the old events
     * and subscribes it to the ones needed for the state
     */
    virtual void manageEvents() = 0;

    StateEnum getState()
    {
        return this->state;
    }

    String getValue()
    {
        switch (this->state)
        {
        case StateEnum::UNCONNECTED:
            return UNCONNECTED_STATE;
        case StateEnum::AUTOMATIC:
            return AUTOMATIC_STATE;
        case StateEnum::MANUAL:
            return MANUAL_STATE;
        }
    }

private:
    StateEnum state;
};