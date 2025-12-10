#pragma once

class Task
{
public:
    Task(/* args */);
    ~Task();

    /*
     * Execute the task.
     * Returns true if the task has ended and should be removed from the scheduler.
     * Returns false if the task is still ongoing.
     */
    virtual bool excecute();
};