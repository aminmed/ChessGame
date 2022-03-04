#ifndef QUEEN_H
#define QUEEN_H
#include "Board.h"
class Queen : public Piece
{
private:
    /* data */
public:
    Queen(bool isBlack);
    ~Queen();
    bool canMove(Board* board, Spot* start, Spot* end);

};

#endif