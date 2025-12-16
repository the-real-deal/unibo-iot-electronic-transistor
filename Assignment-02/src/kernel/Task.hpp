#pragma once

class Task
{
public:
    Task() : id(taskIdCounter), active(false)
    {
        taskIdCounter++;
    }

    /* periodic */
    virtual void init(int period)
    {
        myPeriod = period;
        periodic = true;
        active = true;
        timeElapsed = 0;
    }

    /* aperiodic */
    virtual void init()
    {
        timeElapsed = 0;
        periodic = false;
        active = true;
        completed = false;
    }

    virtual void excecute();
    virtual void cleanup();

    bool updateAndCheckTime(int basePeriod)
    {
        timeElapsed += basePeriod;
        if (timeElapsed >= myPeriod)
        {
            timeElapsed = 0;
            return true;
        }
        else
        {
            return false;
        }
    }

    void setCompleted()
    {
        completed = true;
        // active = false;
        cleanup();
    }

    bool isCompleted()
    {
        return completed;
    }

    bool isPeriodic()
    {
        return periodic;
    }

    bool isActive()
    {
        return active;
    }

    int getPeriod()
    {
        return myPeriod;
    }

    virtual void setActive(bool active)
    {
        timeElapsed = 0;
        this->active = active;
    }

    int getId()
    {
        return id;
    }

private:
    int id;
    int myPeriod;
    int timeElapsed;
    bool active;
    bool periodic;
    bool completed;
    static int taskIdCounter;
};

int Task::taskIdCounter = 0;