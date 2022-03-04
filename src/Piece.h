#ifndef PIECE_H
#define PIECE_H
#include <string>
class Spot;
class Board; 

class Piece {
    private :
        char type = ' ';
        bool killed = false; 
        bool black = false;
        std::string printedValue = " "; 
    public :
    Piece(bool isBlack); 
    ~Piece(); 
    Piece(); 
    bool isKilled();
    bool isBlack();
    void setKilled();
    void setBlack();
    void setType(char t);
    char getType();  
    void setPrintedValue(std::string value); 
    std::string getPrintedValue(); 
    bool virtual canMove(Board* board,Spot* start, Spot* end) = 0;
    bool canSaveKing(Board* board, bool black); 


}; 
#endif 