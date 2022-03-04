#ifndef SPOT_H
#define SPOT_H
#include "Piece.h"
class Spot
{
private:
    Piece* piece;
    int x; 
    int y; 
    bool black;
    bool occupied = false; 
public:
    Spot(Piece* p, int x, int y, bool black);
    ~Spot();
    int getX(); 
    int getY(); 
    Piece* getPiece(); 
    void setPiece(Piece* piece);
    void setX(int x);
    void setY(int y);
    void setOccupied(bool occ);
    bool isOccupied(); 
};



#endif