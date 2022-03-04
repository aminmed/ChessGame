#include "Rook.h"
#include <iostream>
#define WHITE_ROOK  "\u2656"
#define BLACK_ROOK  "\u265C"
Rook::Rook(bool isBlack): Piece(isBlack)
{
    if(isBlack)this->setPrintedValue(BLACK_ROOK); 
    else this->setPrintedValue(WHITE_ROOK); 
    this->setType('R');  
}

Rook::~Rook()
{
}

bool Rook::canMove(Board* board, Spot* start, Spot* end) {
    if(this != start->getPiece()) return false; 
    int startX = start->getX(), startY = start->getY();
    int endX = end->getX(), endY = end->getY();
    if((startX == endX) && (startY == endY)) return false; 
    if(startX == endX) {
        int stepY = (endY - startY >0)? 1:-1; 
        int interY = startY; 
        interY += stepY;
        while(interY!=endY) {
            if (board->getSpot(startX,interY)->isOccupied()) return false;
            interY += stepY; 
        }
        if(end->getPiece() == NULL) return true; 
        return (end->getPiece()->isBlack() == !this->isBlack());
    }
    if(startY == endY) {
        int stepX = (endX - startX>0)? 1:-1; 
        int interX = startX; 
        interX += stepX; 
        while(interX!=endX) {
            if (board->getSpot(interX,startY)->getPiece() != NULL) return false;
            interX += stepX; 
        }
        if(end->getPiece() == NULL) return true; 
        return (end->getPiece()->isBlack() == !this->isBlack());
    }
    return false; 
}
bool Rook::isMoved() {return this->moved;}
void Rook::setMoved() {this->moved = true;}