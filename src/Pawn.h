#ifndef PAWN_H
#define PAWN_H
#include "Board.h"

class Pawn : public Piece
{
private:
    bool moved = false; 
public:
    Pawn(bool isBlack);
    ~Pawn();
    bool canMove(Board* board, Spot* start, Spot* end);
    bool getMoved(); 
    void setMoved(bool moved); 
};


#endif