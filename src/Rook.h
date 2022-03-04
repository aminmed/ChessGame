#ifndef ROOK_H
#define ROOK_H
#include "Board.h"
class Rook : public Piece
{
private:
    bool moved = false; 
public:
    Rook(bool isBlack);
    ~Rook();
    bool canMove(Board* board, Spot* start, Spot* end);
    bool isMoved(); 
    void setMoved(); 
};


#endif