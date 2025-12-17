#pragma once
#include "../Context.hpp"
#include "../../HWPlatform.hpp"

enum HangarSubState
{
    CHECKING,
    OPENING,
    DETECTING,
    CLOSING
};

class HangarState
{
private:
protected:
    Context *context;
    HangarSubState currentSubState;
    int *taskAdded;

public:
    HangarState();
    ~HangarState()
    {
        delete taskAdded;
    }

    void setContext(Context *ctx)
    {
        this->context = ctx;
    }

    /*
     * Adds all the necessary tasks for the state
     */
    virtual void initializeTasks(HWPlatform *platform);

    /*
     * Gets all the data to send to the DRU
     */
    virtual String sendDRUData();

    /*
     * Gets information about the current state (used for LCD display)
     */
    virtual String getStateInfo();

    /*
     * Method to change state, called by external events (ex. tasks)
     */
    virtual void changeState();

    /*
     * Method to handle incoming DRU requests
     */
    virtual void handleRequest(String msg);
};