#include "Queen.h"
#include <iostream>

#define WHITE_QUEEN  "\u2655"
#define BLACK_QUEEN  "\u265B"

Queen::Queen(bool isBlack): Piece(isBlack)
{ 
    if(isBlack) this->setPrintedValue(BLACK_QUEEN);
    else this->setPrintedValue(WHITE_QUEEN);
    this->setType('Q'); 
}

Queen::~Queen()
{
}

bool Queen::canMove(Board* board, Spot* start, Spot* end) {
    if(this != start->getPiece()) return false; 
    int startX = start->getX(), startY = start->getY();
    int endX = end->getX(), endY = end->getY();
    if((startX == endX)&&(startY == endY)) return false; 
    //verify if the end spot is on horizantal or vertical line: same as Rook 
    if(startX == endX) {
        int stepY = (endY - startY > 0)? 1:-1; 
        int interY = startY; 
        interY += stepY;
        while(interY!=endY) {
            if (board->getSpot(startX,interY)->isOccupied()) return false;
            interY += stepY;
        }
        if(end->getPiece()==NULL) return true; 
        return (end->getPiece()->isBlack() == !this->isBlack());
    }
    if(startY == endY) {
        
        int stepX = (endX - startX >0)? 1:-1; 
        int interX = startX;  
        interX += stepX; 
        while(interX!=endX) {
            if (board->getSpot(interX,startY)->isOccupied()) return false;
            interX += stepX; 
        }
        if(end->getPiece()==NULL) return true; 
        return (end->getPiece()->isBlack() != this->isBlack());
    }
    //verify if the end is on diagonal line : same as bishop
    float a = (endX-startX); 
    float b = (endY - startY); 
    float slop = a /b; 
    int interX=startX,interY=startY; 
    if((slop == 1.0) || (slop == -1.0)) {
        int incX = 1,incY = 1; 
        if(endX-startX <0) {
            incX = -1; 
        }
        if(endY-startY <0) {
            incY = -1; 
        }
        interY += incY; 
        interX += incX; 
        while(interX != endX) { 
            if (board->getSpot(interX,interY)->isOccupied()) return false;
            interY += incY; 
            interX += incX; 
        }
        if(end->getPiece()==NULL) return true; 
        return (end->getPiece()->isBlack() == !this->isBlack());
    }
    //All other cases are not possible  
    return false; 
}