#pragma once

#include "Task.hpp"

class Scheduler
{
private:
    /* data */
public:
    Scheduler() {};
    virtual ~Scheduler() {};

    virtual void addTask(Task *t) = 0;
    virtual void removeTask(int id) = 0;
    virtual void executeTask() = 0;
    virtual void clearQueue() = 0;
};