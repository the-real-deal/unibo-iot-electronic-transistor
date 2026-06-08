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
        this->_state = state;
    }
    virtual ~State() = default;

    /**
     * Unsubscribes the handler from the old events
     * and subscribes it to the ones needed for the state
     */
    virtual void manageEvents() = 0;

    StateEnum getState()
    {
        return this->_state;
    }

    String getValue()
    {
        if (this->_state == StateEnum::AUTOMATIC)
        {
            return AUTOMATIC_STATE;
        }
        if (this->_state == StateEnum::MANUAL)
        {
            return MANUAL_STATE;
        }
        if (this->_state == StateEnum::UNCONNECTED)
        {
            return UNCONNECTED_STATE;
        }
        return F("");
    }

private:
    StateEnum _state;
};