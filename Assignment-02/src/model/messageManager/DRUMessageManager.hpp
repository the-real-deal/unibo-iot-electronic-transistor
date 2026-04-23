#pragma once
#include "Arduino.h"

class DRUMessageManager
{
private:
    DRUMessageManager() {}

public:
    // static DRUMessageManager &instance()
    // {
    //     static DRUMessageManager manager;
    //     return manager;
    // }

    // Delete copy constructor and assignment to enforce singleton
    DRUMessageManager(const DRUMessageManager &) = delete;
    DRUMessageManager &operator=(const DRUMessageManager &) = delete;

    String receiveMSG();
    void sendMSG(const String &msg);
};

extern DRUMessageManager Messanger;