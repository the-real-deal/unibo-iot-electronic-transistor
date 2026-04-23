#pragma once

static int taskIdCounter = 0;

/**
 * !!! IMPORTANT !!!
 * These types MUST be in the same order as in the scheduler array.
 */
enum TasksType
{
    BUTTON_TASK = 0,
    DRU_TASK,
    LCD_TASK,
    BLINK_TASK,
    READ_DISTANCE_TASK,
    READ_PIR_TASK,
    READ_TEMP_TASK,
    SWEEPING_TASK
};

class Task
{
public:
    Task() : id(taskIdCounter), active(false)
    {
        taskIdCounter++;
    }

    virtual ~Task() = default;

    /* periodic */
    virtual int init(int period)
    {
        myPeriod = period;
        periodic = true;
        active = true;
        timeElapsed = 0;
        completed = false;

        return this->id;
        // When a state adds his tasks to the scheduler, it keeps track of the task added,
        // on state change all the tasks added by the state are removed.
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
