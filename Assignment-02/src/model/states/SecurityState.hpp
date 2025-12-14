#pragma once
#include "Context.hpp"

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

    virtual char *sendDRUData();
    virtual void recieveDRUData();
};
