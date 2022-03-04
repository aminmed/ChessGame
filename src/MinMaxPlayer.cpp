#include "MinMaxPlayer.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include <iostream>

int pawnTable [8][8] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        50, 50, 50, 50, 50, 50, 50, 50,
        10, 10, 20, 30, 30, 20, 10, 10,
        5,  5, 10, 27, 27, 10,  5,  5,
        0,  0,  0, 25, 25,  0,  0,  0,
        5, -5,-10,  0,  0,-10, -5,  5,
        5, 10, 10,-25,-25, 10, 10,  5,
        0,  0,  0,  0,  0,  0,  0,  0
    };
int knightTable [8][8] = {
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-40,-20,-30,-30,-20,-40,-50,
    }; 
int bishopTable[8][8] = {
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  5,  0,  0,  0,  0,  5,-10,
        -20,-10,-40,-10,-10,-40,-10,-20,
    }; 
int rookTable[8][8] = {
         0,  0,  0,  0,  0,  0,  0,  0,
         50,10,  10, 10,  10,  10,10,50,
        -30,  0, 0, 0, 0,  0,  0, -30,
        -30,  0, 0, 0, 0, 0,  0, -30,
        -30,  0, 0, 0, 0, 0, 0, -30,
        -30,  0, 0, 0, 0,  0, 0, -30,
          0,  0,  0, 0,  0,  0,  0,  0,
        0,  0,  0,  50,  50,  0,  0,  0,
    }; 
int kingTable[8][8] = {
    -50,-40,-30,-20,-20,-30,-40,-50,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -30,-10, -20, -30, -30, -20,-10,-30,
    -30,-10, -30, -40, -40, -30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,0, 20, 30, 30, 20,0,-30,
    -30,-30,  0,  0,  0,  0,30,-30,
    -10,-20,30,30,30,30,-20,-10
    }; 
int queenTable[8][8] = {
        -20, -10, -10, -50, -50, -10, -10, -20,
        -10,   0,   0,   0,   0,   0,  0, -10,
        -10,  0, 50, 50, 50, 50, 0, -10,
        -10,  0, 50, 50, 50, 50, 0, -10,
        -10,  0, 50, 50, 50, 50, 0, -10,
        -10,  0, 50, 50, 50, 50, 0, -10,
        -20, -10, -10, -50, -50, -10, -10, -20,
        -10,   0,   0,   0,   0,   0,  0, -10,
    }; 
MinMaxPlayer::MinMaxPlayer(bool isBlack): Player(isBlack, "MinMaxAgent") 
{

}
MinMaxPlayer::~MinMaxPlayer() {}


void MinMaxPlayer::makeMove(Board* board){
    std::pair<std::string,std::string> conf;  
    conf =this->minMaxSearch(board->getConfiguration()); 
    board->setConfiguration(conf); 
}

std::pair<std::string,std::string> MinMaxPlayer::minMaxSearch(std::pair<std::string,std::string> conf) {
    std::vector< std::pair<std::string,std::string>> confs_childs; 
    confs_childs = this->generatePossibleConfigurations(conf, this->isBlack()); 
    int conf_i =0; 
    int eval = -1000,e; 
    for(int i=0; i<confs_childs.size(); i++){
        e = this->evaluateConfiguration(confs_childs[i],this->depth-1,true); 
        if(e>= eval) {
            eval = e; 
            conf_i = i; 
        }
    }
    return confs_childs[conf_i]; 
}

int MinMaxPlayer::evaluateConfiguration(std::pair<std::string,std::string> configuration,int depth, bool min){
    if(depth == 0) return this->estimateconfiguration(configuration);
    bool black = (min)? !this->isBlack():this->isBlack(); 
    std::vector<std::pair<std::string,std::string>> confs_childs = this->generatePossibleConfigurations(configuration,black); 
    int evaluation,e = 0; 
    if(min) evaluation = 1000; 
    else evaluation = -1000; 
    for(int i=0; i<confs_childs.size(); i++) {
        e = this->evaluateConfiguration(confs_childs[i],depth-1,!min);
        if(min) {
            if( e<= evaluation) evaluation = e; 
        } 
        else {
            if(e >= evaluation) evaluation = e; 
        }
    }
return evaluation; 
}
int MinMaxPlayer::estimateconfiguration(std::pair<std::string,std::string> configuration) {
    Board* b = new Board(); 
    b->setConfiguration(configuration); 
    Piece* piece; 

    int score = 0; 
    // material scores 
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            piece = b->getSpot(i,j)->getPiece(); 
            if(piece != NULL) {
                switch(piece->getType()) {
                    case 'P':
                    score+= (this->isBlack() == piece->isBlack())? pawnTable[7-i][j]:-pawnTable[7-i][j]*0; 

                    break; 
                    case 'Q':
                    score+= (this->isBlack() == piece->isBlack())? queenTable[7-i][j]:-queenTable[7-i][j]*0; 
                    break; 
                    case 'R':
                    score+= (this->isBlack() == piece->isBlack())? rookTable[7-i][j]:-rookTable[7-i][j]*0; 
                    break; 
                    case 'N':
                    score+= (this->isBlack() == piece->isBlack())? knightTable[7-i][j]:-knightTable[7-i][j]*0; 
                    break; 
                    case 'B':
                    score+= (this->isBlack() == piece->isBlack())? bishopTable[7-i][j]:-bishopTable[7-i][j]*0; 
                    break; 
                    case 'K':
                    score+= (this->isBlack() == piece->isBlack())? kingTable[7-i][j]:-kingTable[7-i][j]*0; 
                    break; 
                    default: 
                    score+=0; 
                    break; 
                }
            }
        }
    }
    return score/800; 
}

std::vector<std::pair<std::string,std::string>> MinMaxPlayer::generatePossibleConfigurations(std::pair<std::string,std::string> conf, bool black) 
{
    Board * board= new Board(); 
    board->setConfiguration(conf); 
    Spot* start = NULL; Spot* end = NULL; 
    std::vector<std::pair<std::string,std::string>> confs; 
    Piece* piece = NULL; 
    Piece* pieceToKill = NULL; 
    std::pair<std::string,std::string> configuration; 
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            start = board->getSpot(i,j); 
            piece = start->getPiece(); 
            if(piece != NULL){
            if(piece->isBlack() == black) {
                for(int ii=0; ii<8; ii++) {
                    for(int jj=0; jj<8; jj++) { 
                        end = board->getSpot(ii,jj); 
                        if(piece->canMove(board,start,end)){
                            pieceToKill = end->getPiece(); 
                            if(pieceToKill!= NULL && pieceToKill->isBlack() == black) {
                                start->setOccupied(true); 
                                start->setPiece(pieceToKill); 
                            } else{
                                end->setOccupied(true);
                                start->setOccupied(false); 
                                start->setPiece(NULL); 
                                if(7*black == ii && piece->getType() == 'P') {
                                        Queen* q = new Queen(black);
                                        end->setPiece(q);
                                        confs.push_back(board->getConfiguration()); 
                                        Rook* r = new Rook(black);
                                        end->setPiece(r);
                                        confs.push_back(board->getConfiguration());
                                        Knight* n = new Knight(black);
                                        end->setPiece(n);
                                        confs.push_back(board->getConfiguration());
                                }else{
                                    end->setPiece(piece); 
                                    confs.push_back(board->getConfiguration());
                                }
                                // reset pieces ! 
                                end->setPiece(pieceToKill); 

                                if(pieceToKill == NULL) end->setOccupied(false);
                                else  end->setOccupied(true);  
                                start->setOccupied(true); 
                                start->setPiece(piece); 
                            }
                        }
                    }
                }
            }
            }

        }
    }
    return confs;
}