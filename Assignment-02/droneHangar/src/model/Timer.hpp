#pragma once

class Timer
{
private:
    unsigned long startTime;
    unsigned long stopInit;
    unsigned long elapsedInterruption;
    bool isStopped;
    bool isReset;
public:
    Timer() = default;
    ~Timer() = default;

    /**
     * Starts the timer
     */
    void init();

    /**
     * Checks if a set amount of time has passed since the timer started or reset.
     * @param sec The target time in seconds
     */
    bool hasExeeded(unsigned int sec);
    
    /**
     * Restarts the timer from zero
     */
    void reset();

    /**
     * Stops the timer, it can be resumed.
     */
    void stop();

    /**
     * Resumes the timer, only available if the timer was previeously stopped.
     */
    void resume();

    /**
     * Checks if the timer is currently running
     */
    bool isRunning();
};
