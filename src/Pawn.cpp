#include "Pawn.h"
#define WHITE_PAWN "\u2659"
#define BLACK_PAWN "\u265F"
Pawn::Pawn(bool isBlack): Piece(isBlack)
{ 
    if(isBlack)this->setPrintedValue(BLACK_PAWN);
    else this->setPrintedValue(WHITE_PAWN);
    this->setType('P'); 
    this->moved = false;  
}
bool Pawn::getMoved() {return this->moved;}
void Pawn::setMoved(bool moved) {this->moved = moved;}
Pawn::~Pawn()
{
}
bool Pawn::canMove(Board* board, Spot* start, Spot* end)
{ 
    if(this != start->getPiece()) return false;  
    int startX = start->getX(), startY = start->getY();
    int endX = end->getX(), endY = end->getY();
    Piece* p = NULL; 
    //Is the path from startX to endX a possible path for pawn :
    if(!this->isBlack()) {
        if(startX == 1) {
            if((endX > startX+2)||(endX <= startX)) return false;
            if((startX +2 == endX)&&(startY != endY)) return false;  
        }else{
            if((endX> startX+1) || (endX <= startX)) return false;  
        }
    }
    else{
        if(startX == 6) {
            if((endX < startX-2)||(endX >= startX)) return false;
             if((startX-2 == endX)&&(startY != endY)) return false;
        }else{
            if((endX<startX-1) || (endX >= startX)) return false;  
        }
    }
    //Is the path from startY to endY a possible path for pawn 
    if((endY > startY + 1)||(endY < startY - 1)) return false;  
    
    int step = 1; 
    if(this->isBlack()) {
        step =-1; 
    }
    //verify if the target spot is possible or there is an enemy
    if(endY == startY){
       if(startX+step  == endX){
           return !end->isOccupied(); 
       }else{ 
           if((!end->isOccupied())&& (!board->getSpot(endX-step,endY)->isOccupied())) return true; 

       }
    }else{
        if(end->getPiece() == NULL){
            p = board->getSpot(startX,endY)->getPiece();
            //if(p == NULL) p = board->getSpot(endX,startY)->getPiece();
            if(p == NULL) {
                return false; 
                } 
            if(p->isBlack() == this->isBlack()) return false;   
            if(p != NULL && p->getType() == 'P'){
                return ((Pawn*)p)->getMoved(); 
            }
            return false; 
        } 
        return (end->isOccupied()&& (end->getPiece()->isBlack() == !this->isBlack())); 
    }
return false; 
}