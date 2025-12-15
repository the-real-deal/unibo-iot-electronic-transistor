#pragma once
#include "Context.hpp"
#include "../HWPlatform.hpp"

class HangarState
{
private:
protected:
    Context *context;

public:
    HangarState();
    ~HangarState();

    void setContext(Context *ctx)
    {
        this->context = ctx;
    }

    virtual void initializeTasks(HWPlatform *platform);
    virtual void changeState();
};