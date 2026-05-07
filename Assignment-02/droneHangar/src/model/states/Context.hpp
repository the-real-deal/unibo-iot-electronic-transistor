#pragma once
#include <Arduino.h>
#include <LinkedList.h>
#include "kernel/Task.hpp"
#include "kernel/Scheduler.hpp"
#include "model/HWPlatform.hpp"
#include "model/InputHolder.hpp"

/**
 * State pattern concepts taken from:
 * Title: Design Patterns: Elements of Reusable Object-Oriented Software
 * Author: Gang of Four
 * Pages: 283-291
 */

/* State Classes Definition */
class HangarState;
class SecurityState;
enum HangarSubState
{
    CHECKING,
    OPENING,
    DETECTING,
    CLOSING
};

enum ContextType
{
    HANGAR,
    SECURITY
};

/* ------------------------ */

class Context
{
private:
    HangarState *hangarState;
    SecurityState *securityState;
    Scheduler *scheduler;
    InputHolder *holder;

public:
    Context(Scheduler *sched, InputHolder *holder);
    virtual ~Context() = 0;

    /*
     * Setters for the hangar state, method called by the states themselves
     */
    virtual void setHangarState(HangarState *state) = 0;
    /*
     * Setters for the security state, method called by the states themselves
     */
    virtual void setSecurityState(SecurityState *state) = 0;

    /*
     * Method called by tasks (ex. pir read), checks the condition for the state change
     */
    virtual void checkUpdate(ContextType destinationCtx) = 0;

    /*
     * Method to handle incoming DRU requests
     */
    virtual void handleDRURequest() = 0;

    /*
     * Method used to add tasks to the scheduler
     */
    virtual void addTaskToScheduler(Task *task, int period) = 0;

    /**
     * Method used to remove task from the scheduler
     */
    virtual void removeTaskFromScheduler(int id) = 0;
};

/**
 * Possible update: create a general state class containing:
 * - context and list oadded tasks
 * - destructor
 * - set context and add task methods
 * to avoid code duplications
 */
/* State Class Definition */
class HangarState
{
private:
protected:
    Context *context;
    LinkedList<int> taskAdded = LinkedList<int>();
    HWPlatform *hwPlatform;
    InputHolder *inputHolder;

public:
    HangarState(HWPlatform *platform, InputHolder *holder) : hwPlatform(platform), inputHolder(holder) {}
    virtual ~HangarState()
    {
        removeAddedTasks();
    }

    void setContext(Context *ctx)
    {
        if (this->context == nullptr)
            this->context = ctx;
    }

    /**
     * Adds a task and saves its id to a list.
     */
    void addTask(Task *t, int period)
    {
        this->context->addTaskToScheduler(t, period);
        this->taskAdded.add(t->getId());
    }

    void removeAddedTasks()
    {
        int listSize = this->taskAdded.size();

        for (int i = 0; i < listSize; i++)
        {
            this->context->removeTaskFromScheduler(this->taskAdded.get(i));
        }

        this->taskAdded.clear();
    }

    /*
     * Adds all the necessary tasks for the state
     */
    virtual void initializeTasks() = 0;

    /*
     * Method to change state, called by external events (ex. tasks)
     */
    virtual void checkUpdate() = 0;
};

class SecurityState
{
private:
protected:
    Context *context;
    LinkedList<int> taskAdded = LinkedList<int>();
    HWPlatform *hwPlatform;
    InputHolder *inputHolder;

public:
    SecurityState(HWPlatform *platform, InputHolder *holder) : hwPlatform(platform), inputHolder(holder) {}
    virtual ~SecurityState()
    {
        removeAddedTasks();
    };

    void setContext(Context *ctx)
    {
        if (this->context == nullptr)
            this->context = ctx;
    }

    /**
     * Adds a task and saves its id to a list.
     */
    void addTask(Task *t, int period)
    {
        this->context->addTaskToScheduler(t, period);
        this->taskAdded.add(t->getId());
    }

    void removeAddedTasks()
    {
        int listSize = this->taskAdded.size();

        for (int i = 0; i < listSize; i++)
        {
            this->context->removeTaskFromScheduler(this->taskAdded.get(i));
        }

        this->taskAdded.clear();
    }

    /*
     * Adds all the necessary tasks for the state
     */
    virtual void initializeTasks() = 0;

    /*
     * Method to check if the current state can receive messages
     */
    virtual bool canReceiveMsg() = 0;

    /*
     * Method to change state, called by external events (ex. tasks)
     */
    virtual void checkUpdate() = 0;
};
