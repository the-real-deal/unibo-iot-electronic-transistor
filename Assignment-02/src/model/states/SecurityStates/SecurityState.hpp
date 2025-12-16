#pragma once
#include "../Context.hpp"
#include "../../HWPlatform.hpp"

class SecurityState
{
private:
protected:
    Context *context;

public:
    SecurityState(/* args */);
    ~SecurityState();
    void setContext(Context *ctx)
    {
        this->context = ctx;
    }

    virtual void initializeTasks(HWPlatform *platform);
    virtual void recieveDRUData(String data);
    virtual String sendDRUData();
    virtual String getStateInfo();
    virtual void changeState();
};
