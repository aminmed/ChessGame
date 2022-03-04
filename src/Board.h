#ifndef BOARD_H
#define BOARD_H
#include "Spot.h"
#include <vector>
class Board
{                     
private: 
    std::vector<std::vector<Spot>> spots;
    std::vector<Piece*> killedBlackPieces;
    std::vector<Piece*> killedWhitePieces; 
    bool unicode = true;
    void printUnicode(); 
    void printBasic(); 
public:
    Board();
    ~Board();
    void setBoard(); 
    void setUnicode(bool u);  
    std::vector<std::vector<Spot>> getBoard(); 
    void resetBoard();
    void resetEmptyBoard(); 
    void printBoard(); 
    Spot* getSpot(int x, int y); 
    std::vector<Piece*>getKilledPieces(bool isBlack); 
    void killPiece(Piece* p);
    std::pair<int,int> getPiecePosition(bool color,char type,int sX,int sY,char column,char row);  
    bool copyBoard(Board *copy); 
    void saveConfiguration(std::string file); 
    bool readConfiguration(std::string file); 
    bool setConfiguration(std::pair<std::string,std::string> conf); 
    std::pair<std::string,std::string> getConfiguration(); 
};



#endif