#pragma once

static int taskIdCounter = 0;

class Task
{
public:
    Task() : id(taskIdCounter), active(false)
    {
        taskIdCounter++;
    }

    virtual ~Task() = default;

    /* periodic */
    virtual void init(int period)
    {
        myPeriod = period;
        periodic = true;
        active = true;
        timeElapsed = 0;
        completed = false;
    }

    /* aperiodic */
    virtual void init()
    {
        timeElapsed = 0;
        periodic = false;
        active = true;
        completed = false;
    }

    virtual void execute() = 0;
    virtual void cleanup() = 0;
    // virtual void setup() = 0;

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
        active = false;
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
};
