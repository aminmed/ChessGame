#ifndef BISHOP_H
#define BISHOP_H
#include "Board.h"
class Bishop : public Piece
{
private:
    /* data */
public:
    Bishop(bool isBlack);
    ~Bishop();
    bool canMove(Board* board, Spot* start, Spot* end);
};


#endif