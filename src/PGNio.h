#ifndef PGNIO_H
#define PGNIO_H
#include "Move.h"
#include "Board.h"
#include "Player.h"
#include <vector>
class PGNio 
{
private:
    std::string filePath;
    std::vector<std::pair<std::string,std::string>> headers;
    std::vector<Move*> moves;
    bool readOnly = true; // file is a source file for reading 
    int turns = 0;
    std::string result = "*"; 
    Move *extractMove(bool black,Board* board,std::string step); 
    std::pair<std::string,std::string> extractHeaderData(std::string header);
    std::string removeComments(std::string w); 
public:
    PGNio(std::string file, bool readOnly);
    ~PGNio();
    Board* readMovesFromPGN(int turnId); 
    bool writeMovesToPGN(std::string file);
    std::vector<Move*> getMoves(); 
    void printHeaders(); 
    std::string getBlackPlayerName(); 
    std::string getWhitePlayerName();
    std::string getResult();
    void setResult(std::string result); 
    void setHeaders(std::vector<std::pair<std::string,std::string>> headers); 
    std::string getFileName(); 
    Move* getMoveById(int i); 
    void addMove(Move* move);
    bool resetMoves(); 
};


#endif