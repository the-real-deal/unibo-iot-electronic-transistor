#pragma once
class State
{

public:
    virtual ~State() = default;

    /**
     * Unsubscribes the handler from the old events
     * and subscribes it to the ones needed for the state
     */
    virtual void manageEvents() = 0;

private:
    /* data */
};