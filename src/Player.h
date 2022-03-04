#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include "Move.h"
#include <vector>
#include <string>

class Player
{
private:
    std::string name; 
    bool black; 
    std::vector<Move*> moves; 
    bool resign =false;
    bool askForDraw = false; 
    bool requireThreeFoldRep = false; 
public:
    Player(bool black, std::string name);
    ~Player();
    bool isBlack(); 
    void setName(std::string name); 
    std::string getName(); 
    std::pair<bool,Move*> makeMove(Board *board,int startX,int startY, int endX, int endY); 
    bool casteling(Board *board,bool KingsRook);
    bool pawnPromotion(Board *board,char type, int pawnX, int pawnY);
    bool canSaveKing(Board* board, int startX, int startY); 
    bool check(Board *board); 
    bool checkMate(Board *board);
    bool safeMove(Board* board ,Spot* start, Spot* end); 
    bool staleMate(Board* board); 
    void toResign() ;
    bool isResigned(); 
    void setAskForDraw(bool ask);
    bool getAskForDraw(); 
    void setRequireThreeFoldRep(bool require); 
    bool getRequireThreeFoldRep();
};



#endif