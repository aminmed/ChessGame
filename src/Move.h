#ifndef MOVE_H
#define MOVE_H
#include <string>
class Move
{
private:
    std::string start; // start spot coordinate format PGN a1, a2, b7, f5 ....
    std::string end; // end spot coordinate format PGN a1, a2, b7, f5 ....
    char promotedTo = ' '; // type of piece promoted to a pawn (Q,R,N)
    bool captering = false; 
    char pieceType;  
    int turnId;  // move's id in the Game. 
    
public:
    Move(int currentId,std::string start,std::string end,bool captering, char Piecetype);
    ~Move();
    int getStartX();
    void setStartX(int Y);
    void setStartY(int X);
    int getStartY();
    int getEndX();
    void setEndX(int Y);
    int getEndY();
    void setEndY(int X);
    bool getCaptering(); 
    void setCaptering(bool captering); 
    void setPieceType(char type); 
    std::string getStart(); 
    std::string getEnd();
    char getPieceType(); 
    int getTurnId(); 
    void setTurnId(int turnId); 
    char getPromotedTo();
    void setPromotedTo(char promotedTo); 

};

#endif