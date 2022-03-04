#ifndef KNIGHT_H
#define KNIGHT_H
#include "Board.h"
class Knight : public Piece
{
private:
    /* data */
public:
    Knight(bool isBlack);
    ~Knight();
    bool canMove(Board* board, Spot* start, Spot* end); 
};


#endif