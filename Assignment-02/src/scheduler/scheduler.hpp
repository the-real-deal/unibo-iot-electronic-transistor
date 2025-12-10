#pragma once

#include "task.hpp"

class scheduler
{
private:
    /* data */
public:
    scheduler(/* args */);
    ~scheduler();

    virtual bool addTask(Task t) = 0;
    virtual bool removeTask(int id) = 0;
    virtual void excecuteTask() = 0;
    virtual void clearQueue() = 0;
};