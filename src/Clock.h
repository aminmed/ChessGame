#ifndef CLOCK_H
#define CLOCK_H
#include <string>
#include <chrono>

typedef std::chrono::seconds Seconds;

class Clock
{
private:
    std::string type; 
    Seconds remainingSecondsForBlack; 
    Seconds remainingSecondsForWhite; 
    Seconds secondsToAddAfterMove;
public:
    Clock(std::string type, Seconds intialBlack,
    Seconds intialWhite,
    Seconds secondsToAddAfterMove); 
    ~Clock();
    Seconds getRemainingSecondsForBlack();
    Seconds getRemainingSecondsForWhite();
    bool incRemainingSecondsForWhite(Seconds seconds); 
    bool incRemainingSecondsForBlack(Seconds seconds);
    bool decRemainingSecondsForBlack(Seconds seconds);
    bool decRemainingSecondsForWhite(Seconds seconds);
    std::string getClockType();
    Seconds getClockInc(); 
};

#endif