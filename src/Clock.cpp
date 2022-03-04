#include "Clock.h"

Clock::Clock(std::string type, Seconds intialBlack,
 Seconds intialWhite,Seconds secondsToAddAfterMove)
{
    this->type = type; 
    this->remainingSecondsForBlack = intialBlack; 
    this->remainingSecondsForWhite = intialWhite; 
    this->secondsToAddAfterMove    = secondsToAddAfterMove; 
}

std::string Clock::getClockType() {return this->type;}
Seconds Clock::getClockInc(){return this->secondsToAddAfterMove;}
Clock::~Clock()
{
}
Seconds Clock::getRemainingSecondsForBlack() {
    return this->remainingSecondsForBlack; 
}
Seconds Clock::getRemainingSecondsForWhite() {
    return this->remainingSecondsForWhite; 
}
bool Clock::incRemainingSecondsForBlack(Seconds seconds){
    if(seconds > this->secondsToAddAfterMove) return false; 
    this->remainingSecondsForBlack += seconds; 
    return true; 
}
bool Clock::incRemainingSecondsForWhite(Seconds seconds) {
    if(seconds > this->secondsToAddAfterMove) return false;
    this->remainingSecondsForWhite += seconds;
    return true;  
}
bool Clock::decRemainingSecondsForBlack(Seconds seconds) {
    this->remainingSecondsForBlack -= seconds;
    return  this->remainingSecondsForBlack.count() > 0; 
}
bool Clock::decRemainingSecondsForWhite(Seconds seconds) {
    this->remainingSecondsForWhite -= seconds;
    return  this->remainingSecondsForWhite.count() > 0; 
}
