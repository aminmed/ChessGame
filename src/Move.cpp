#include "Move.h"

Move::Move(int currentId, std::string start, std::string end, bool captering, char pieceType)
{
    this->start = start; 
    this->end = end; 
    this->pieceType = pieceType;
    this->captering = captering; 
    this->turnId = currentId; 
    this->promotedTo = ' '; 
}

Move::~Move()
{}
int Move::getStartY() {
    return this->start[0] - 'a'; 
}
int Move::getEndY() {
    return this->end[0] - 'a'; 
}
int Move::getStartX() {
    return  this->start[1] - '1'; 
}
int Move::getEndX() {
    return  this->end[1] - '1'; 
}
void Move::setStartY(int Y) {
    this->start[0] = Y + 'a'; 
}
void Move::setEndY(int Y) {
    this->end[0] = Y + 'a'; 
}
void Move::setEndX(int X) {
    this->end[1] = X + '1'; 
}
void Move::setStartX(int X) {
    this->start[1] = X + '1'; 
}
std::string Move::getStart(){return this->start;}
std::string Move::getEnd(){return this->end;}
bool Move::getCaptering(){return this->captering;}
void Move::setCaptering(bool captering){this->captering = captering;}
int Move::getTurnId(){return this->turnId;}
void Move::setPromotedTo(char promotedTo) {this->promotedTo = promotedTo; }
char Move::getPromotedTo(){return this->promotedTo; }
char Move::getPieceType() {return this->pieceType;}
void Move::setTurnId(int turnId) {this->turnId = turnId; }

