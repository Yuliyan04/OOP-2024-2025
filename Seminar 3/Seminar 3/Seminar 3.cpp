#include <iostream>



constexpr size_t SECONDS_IN_DAY = 3600 * 24;
constexpr size_t SECONDS_IN_MINUTE = 60;
constexpr size_t SECONDS_IN_HOUR = 3600;

class Time
{
    unsigned secondsFromMidnight;

    bool validateAndSetSeconds(unsigned seconds)
    {
        if (seconds <= SECONDS_IN_DAY)
        {
            return true;
        }

        return false;
    }

    bool validateAndSet(unsigned toSet, unsigned min, unsigned max, unsigned mult, unsigned prev)
    {
        if (toSet >= min && toSet <= max)
        {
            secondsFromMidnight -= ((prev * mult) + (toSet * mult)); 
            return true;
        }
        return false;
    }

public:
    Time() : secondsFromMidnight(0) {}
    Time(unsigned seconds)
    {
        if (validateAndSetSeconds(seconds))
        {
            secondsFromMidnight = seconds;
        }
        else
        {
            Time();
        }
    }
    Time(unsigned hours, unsigned mins, unsigned seconds)
    {
        setSeconds(seconds);
        setMins(mins);
        setHours(hours);
    }

    bool setSeconds(unsigned seconds)
    {
        return validateAndSet(seconds, 0, 59, 1, getSeconds());
    }

    bool setMins(unsigned mins)
    {
        return validateAndSet(mins, 0, 59, 60, getMins());
    }

    bool setHours(unsigned hours)
    {
        return validateAndSet(hours, 0, 23, 3600, getHours());
    }

    unsigned getHours() const
    {
        return secondsFromMidnight / SECONDS_IN_HOUR;
    }

    unsigned getMins() const
    {
        return (secondsFromMidnight / SECONDS_IN_MINUTE) % SECONDS_IN_MINUTE;
    }

    unsigned getSeconds() const
    {
        return secondsFromMidnight % SECONDS_IN_MINUTE;
    }

    unsigned toSeconds() const
    {
        return secondsFromMidnight;
    }

    void printTime() const
    {

    }

    Time substract(const Time& other)
    {
        if (other.secondsFromMidnight > secondsFromMidnight)
        {
            return {};
        }

        unsigned newTime = secondsFromMidnight - other.secondsFromMidnight;
        Time t(newTime);

        return t;
    }

};


int main()
{
    std::cout << "Hello World!\n";
}

