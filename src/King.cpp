#include "King.h"
#define WHITE_KING "\u2654"
#define BLACK_KING "\u265A"
King::King(bool isBlack): Piece(isBlack)
{ 
   if(isBlack) this->setPrintedValue(BLACK_KING);
   else this->setPrintedValue(WHITE_KING); 
   this->setType('K'); 
}

King::~King()
{
} 
bool King::canMove(Board* board, Spot* start, Spot* end) { 
    if(this != start->getPiece()) return false; 
    int startX = start->getX(), startY = start->getY();
    int endX = end->getX(), endY = end->getY();
    if((startX == endX)&&(startY == endY)) return false; 
   // if (this->safeSpot(board,end) == false) return false; 
    if(((startX == endX -1)||(startX == endX +1)||(startX == endX))&&((startY == endY -1)||(startY == endY +1)||(startY == endY))){
        if(end->getPiece()==NULL) return true; 
        return (end->getPiece()->isBlack() == !this->isBlack()); 
    }else {
        return false; 
    }
}

bool King::isThreatened(Board *board){
    bool threatened = false; 
    Spot *currentSpot;
    Spot* kingSpot = NULL;  
    Piece* piece; 
    for(int x=0;x<8;x++) {
        for(int y=0; y<8;y++){
            currentSpot = board->getSpot(x,y);
            piece = currentSpot->getPiece();
            if(piece!=NULL){
                if(piece->getType()=='K' && piece->isBlack() == this->isBlack()) {
                    kingSpot = currentSpot; 
                }
            } 
        }
    }
    for(int x=0;x<8;x++) {
        for(int y=0; y<8;y++){
                currentSpot = board->getSpot(x,y);  
                piece = currentSpot->getPiece();
                if(piece != NULL) {
                    if(piece->isBlack() != this->isBlack()) {
                        if(piece->canMove(board,currentSpot,kingSpot)) {
                            threatened = true; 
                        }
                    }
                }
        }
    }
    return threatened; 
}
bool King::isMoved() {return this->moved;}
void King::setMoved() {this->moved = true;}