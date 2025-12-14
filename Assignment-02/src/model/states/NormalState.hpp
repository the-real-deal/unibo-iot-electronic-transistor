#pragma once
#include "SecurityState.hpp"

class NormalState : public SecurityState
{
private:
    /* data */
public:
    NormalState(/* args */);
    ~NormalState();

    char *sendDRUData() override;
    void recieveDRUData() override;
};
