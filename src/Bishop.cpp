#include "Bishop.h"
#define WHITE_BISHOP  "\u2657"
#define BLACK_BISHOP  "\u265D"
Bishop::Bishop(bool isBlack): Piece(isBlack)
{ 
    if(isBlack) this->setPrintedValue(BLACK_BISHOP);
    else this->setPrintedValue(WHITE_BISHOP);
    this->setType('B');  
}

Bishop::~Bishop()
{
}
bool Bishop::canMove(Board* board, Spot* start, Spot* end) {
    if(this != start->getPiece()) return false; 
    int startX = start->getX(), startY = start->getY();
    int endX = end->getX(), endY = end->getY();
    if((startX == endX) || (startY == endY)) return false; 
    float a = (endX-startX); 
    float b = (endY - startY); 
    float slop = a / b;   
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
        if(end->getPiece() == NULL) return true;  
        return (end->getPiece()->isBlack() != this->isBlack()); 
    }
    return false; 
}