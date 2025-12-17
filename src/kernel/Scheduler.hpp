#pragma once

#include "Task.hpp"

class Scheduler
{
private:
    /* data */
public:
    Scheduler();
    ~Scheduler();

    virtual void addTask(Task t);
    /*
     * Removes a task from the scheduler by its id.
     * Returns the removed task, returns null pointer if no task is found.
     */
    // virtual int removeTask(int id) = 0;
    virtual void excecuteTask();
    virtual void clearQueue();
};