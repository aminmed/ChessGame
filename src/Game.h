#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "Player.h"
#include "MinMaxPlayer.h"
#include "Move.h"
#include "PGNio.h"
#include "Clock.h"
#include <vector>
#include <string>
class Game
{
private:
    Board* board; 
    Player* blackPlayer;
    Player* whitePlayer;
    Clock* clock; 
    bool blackIsPlaying; 
    PGNio* PGNsave = NULL ;
    std::vector<Move*> moves;
    std::vector<std::pair<std::string,std::string>> configurations; 
    int numberOfMoves = 0; 
    std::string result = "*"; 
public:
    Game(Player* blackPlayer, Player* whitePlayer, std::string saveFile, Clock* clock);
    ~Game();
    std::string getResult();
    Board* getBoard();
    bool saveGame();
    bool playMove(bool black,int startX,int startY, int endX,int endY); 
    bool startGame(std::string sourceFile, int turnOfstart);
    std::string getGameResult(); 
    bool deadPosition(); 
    bool threeFoldRep();  
    void setBlackIsPlaying(bool black); 
    bool getBlackIsPlaying();
    Clock* getClock(); 
    void setClock(Clock* c);  
    Player* getWhitePlayer(); 
    Player* getBlackPlayer();
    void playGame();
    void playAgainstAgent();  

};


#endif