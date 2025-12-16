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

    virtual void initializeTasks(HWPlatform *platform);
    virtual char *sendDRUData();
    virtual String getStateInfo();
    virtual void changeState();
};