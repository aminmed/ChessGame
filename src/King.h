#ifndef KING_H
#define KING_H
#include "Board.h"
class King : public Piece
{
private:
    bool moved = false; 
public:
    King(bool isBlack);
    ~King();
    bool canMove(Board* board, Spot* start, Spot* end); 
    bool isThreatened(Board* board); 
    bool safeSpot(Board* board, Spot* spot);
    bool isMoved(); 
    void setMoved(); 
};


#endif