#pragma once

class Task
{
private:
    /* data */
    int id;

protected:
    int duration;

public:
    Task(const int id) : id(id) {};
    ~Task();

    /*
     * Execute the task.
     * Returns true if the task has ended and should be removed from the scheduler.
     * Returns false if the task is still ongoing.
     */
    virtual bool excecute();

    int getId()
    {
        return id;
    }
};