#include "Knight.h"

#define WHITE_KNIGHT "\u2658"
#define BLACK_KNIGHT "\u265E"
Knight::Knight(bool isBlack): Piece(isBlack)
{ 
    if(isBlack)this->setPrintedValue(BLACK_KNIGHT);
    else this->setPrintedValue(WHITE_KNIGHT); 
    this->setType('N'); 
}

Knight::~Knight()
{
}
bool Knight::canMove(Board* board, Spot* start, Spot* end){
    if(this != start->getPiece()) return false; 
    int startX = start->getX(), startY = start->getY();
    int endX = end->getX(), endY = end->getY();
    //Is the path from startX to endX a possible path for pawn :
    if((endX == startX+2)||(endX == startX-2)) { 
        if((endY == startY + 1)||(endY == startY - 1)) {
            if (end->getPiece() == NULL) return true; 
            return (end->getPiece()->isBlack() == !this->isBlack());
        }
    }
    if((endX == startX+1)||(endX == startX-1)) { 
        if((endY == startY + 2)||(endY == startY - 2)) {
            if (end->getPiece() == NULL) return true; 
            return  (end->getPiece()->isBlack() == !this->isBlack());
        }
    }

return false; 
}