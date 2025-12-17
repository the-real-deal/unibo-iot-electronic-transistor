#pragma once

#include "Task.hpp"

class Scheduler
{
private:
    /* data */
public:
    Scheduler();
    ~Scheduler();

    virtual void addTask(Task *t) = 0;
    virtual void removeTask(int id) = 0;
    virtual void excecuteTask() = 0;
    virtual void clearQueue() = 0;
};