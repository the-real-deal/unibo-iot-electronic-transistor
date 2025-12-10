#pragma once

#include "task.hpp"

class scheduler
{
private:
    /* data */
public:
    scheduler(/* args */);
    ~scheduler();

    virtual void addTask(Task t) = 0;
    /*
     * Removes a task from the scheduler by its id.
     * Returns the removed task, returns null pointer if no task is found.
     */
    virtual Task removeTask(int id) = 0;
    virtual void excecuteTask() = 0;
    virtual void clearQueue() = 0;
};