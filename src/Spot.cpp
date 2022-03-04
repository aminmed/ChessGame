#include <iostream>
#include <string>
#include "Spot.h"
Spot::Spot(Piece* p, int x, int y, bool black)
{
    this->piece = p;
    if(this->piece == NULL) this->occupied = false; 
    else this->occupied = true; 
    this->x = x; 
    this->y = y; 
    this->black = black; 
}

Spot::~Spot()
{
}

int Spot::getX(){
    return this->x;
}
int Spot::getY(){return this->y;}
Piece* Spot::getPiece(){return (this->piece);} 
void Spot::setPiece(Piece* piece){this->piece = piece;} 
void Spot::setX(int x){this->x=x;}
void Spot::setY(int y){this->y=y;}
void Spot::setOccupied(bool occ){this->occupied = occ;}
bool Spot::isOccupied(){return this->occupied;}