
class Timer
{
private:
    long startTime;
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
     * Restarts the timer
     */
    void reset();
};
