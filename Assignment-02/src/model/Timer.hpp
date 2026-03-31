
class Timer
{
private:
    long startTime;
    long stopInit;
    long elapsedInterruption;
    bool isStopped;
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
    bool hasExeeded(int sec);
    
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
};
