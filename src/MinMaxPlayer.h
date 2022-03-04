#ifndef MINMAXPLAYER_H
#define MINMAXPLAYER_H
#include "Player.h"

class MinMaxPlayer: public Player
{
private:
    int depth = 3; 
    
public:
    MinMaxPlayer(bool isBlack); 
    ~MinMaxPlayer(); 
    std::vector<std::pair<std::string,std::string>>  generatePossibleConfigurations(std::pair<std::string,std::string> conf, bool black);
    int evaluateConfiguration(std::pair<std::string,std::string> configuration,int depth, bool min);
    void makeMove(Board* board);
    std::pair<std::string,std::string> minMaxSearch(std::pair<std::string,std::string> conf); 
    int estimateconfiguration(std::pair<std::string,std::string> configuration); 
};

#endif