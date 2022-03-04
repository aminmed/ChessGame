#include "Game.h"
#include <fstream>
#include <iostream>
#include <string>
Game::Game( Player* blackPlayer, Player* whitePlayer,std::string saveFile,Clock* clock)
{
    this->blackPlayer = blackPlayer;
    this->whitePlayer = whitePlayer; 
    this->board = new Board(); 
    this->PGNsave = new PGNio(saveFile, false);
    this->blackIsPlaying = false; 
    this->clock = clock; 
    this->numberOfMoves = 1; 
}

Player* Game::getWhitePlayer(){return this->whitePlayer;}
Player* Game::getBlackPlayer(){return this->blackPlayer;}
Game::~Game()
{
}
void Game::setBlackIsPlaying(bool black){
    this->blackIsPlaying = black; 
}
Clock* Game::getClock() {return this->clock; }
void Game::setClock(Clock* c) {this->clock = c; }
bool Game::getBlackIsPlaying(){
    return this->blackIsPlaying; 
}
std::string Game::getResult() {
    return this->result; 
}
Board* Game::getBoard() {
    return this->board; 
}
bool Game::threeFoldRep() {
    int l = this->configurations.size(); 
    int lastConfRep = 0; 
    if(l<3) return false;
    for(int i=0; i<l-1; i++) {
        if(this->configurations[l-1].first == this->configurations[i].first 
    && this->configurations[l-1].second == this->configurations[i].second ) lastConfRep++; 
    } 
    return lastConfRep >=3; 
}
bool Game::saveGame() {
    this->PGNsave->resetMoves(); 
    Move* m; 
    std::vector<std::pair<std::string,std::string>> v; 
    for(int i=0; i<this->moves.size(); i++) {
        m =(this->moves[i]);  
        this->PGNsave->addMove(m); 
    }
    std::pair<std::string,std::string> s; 
    s.first = "White";
    s.second = this->whitePlayer->getName(); 
    v.push_back(s); 
    s.first = "Black";
    s.second = this->blackPlayer->getName(); 
    v.push_back(s);
    s.first = "Result";
    s.second = this->result; 
    v.push_back(s); 
    this->PGNsave->setResult(this->result); 
    this->PGNsave->setHeaders(v); 
    return this->PGNsave->writeMovesToPGN("save"+this->PGNsave->getFileName()); 
}
bool Game::startGame(std::string sourceFile, int turnOfstart){
    if(sourceFile != "") {
        this->PGNsave = new PGNio(sourceFile,false); 
        this->board = this->PGNsave->readMovesFromPGN(turnOfstart); 
        this->blackPlayer->setName(this->PGNsave->getBlackPlayerName()); 
        this->whitePlayer->setName(this->PGNsave->getWhitePlayerName());
        this->result = this->PGNsave->getResult(); 
        return true; 
    }else return false; 
}
bool Game::deadPosition(){
    if(this->blackPlayer->check(this->board)|| this->whitePlayer->check(this->board)) return false; 
    int blackKnights =2; 
    int whiteKnights  =2; 
    int blackBishops  =2;
    int whiteBishops  =2; 
    int whitePawns   =8; 
    int blackPawns   =8; 
    int blackQueen=1; 
    int whiteQueen=1; 
    int blackRooks=2; 
    int whiteRooks=2; 
    std::vector<Piece*> blackPiecesKilled = this->board->getKilledPieces(true); 
    std::vector<Piece*> whitePiecesKilled = this->board->getKilledPieces(false); 
    
    for (int i = 0; i < blackPiecesKilled.size(); i++)
    {
        if(blackPiecesKilled[i]->getType() == 'P') blackPawns--;
        if(blackPiecesKilled[i]->getType() == 'N') blackKnights--; 
        if(blackPiecesKilled[i]->getType() == 'B') blackBishops--;
        if(blackPiecesKilled[i]->getType() == 'Q') blackQueen--;
        if(blackPiecesKilled[i]->getType() == 'R') blackRooks--;
    }   
    for (int i = 0; i < whitePiecesKilled.size(); i++)
    {
        if(whitePiecesKilled[i]->getType() == 'P') whitePawns--;
        if(whitePiecesKilled[i]->getType() == 'N') whiteKnights--; 
        if(whitePiecesKilled[i]->getType() == 'B') whiteBishops--;
        if(whitePiecesKilled[i]->getType() == 'Q') whiteQueen--;
        if(whitePiecesKilled[i]->getType() == 'R') whiteRooks--;
    }
    if(blackRooks <= 0 && blackQueen <= 0 && whiteRooks <= 0 && whiteQueen <= 0){
        if(blackPawns ==0 && whitePawns == 0) {
            if(whiteBishops <= 1 && blackBishops <= 1 && blackKnights ==0 && whiteKnights ==0) return true; 
            if(whiteBishops == 0 && blackBishops == 0) {
                if(blackKnights == 0) return true; 
                if(whiteKnights == 0) return true;
            }
        }

    return false; 
    }
    
    return false; 
}
std::string Game::getGameResult(){
    // One of the players win by checkmate : 
    if(this->blackPlayer->checkMate(this->board)) {
        this->result = "1-0"; 
        return "1-0"; 
    }
    if(this->whitePlayer->checkMate(this->board)) {
        this->result = "0-1"; 
        return "0-1"; 
    }
    
    if(this->whitePlayer->isResigned()) {
        this->result = "0-1"; 
        return "0-1"; 
    }
    if(this->blackPlayer->isResigned()) {
        this->result = "1-0"; 
        return "1-0"; 
    }
    // Flag fall for black ! 
    if(this->clock->getRemainingSecondsForBlack().count() <=0)  {
        this->result = "1-0"; 
        return "1-0"; 
    }
    // Flag fall for white ! 
    if(this->clock->getRemainingSecondsForWhite().count() <=0)  {
        this->result = "0-1"; 
        return "0-1"; 
    }
    // draw !!
    // staleMate : 
    if(this->blackIsPlaying && this->blackPlayer->staleMate(this->board)) {
        this->result = "1/2-1/2";
        return "1/2-1/2"; 
    }
    if(!this->blackIsPlaying && this->whitePlayer->staleMate(this->board)) {
        this->result = "1/2-1/2";
        return "1/2-1/2"; 
    }
    if(this->blackPlayer->getRequireThreeFoldRep() && this->blackIsPlaying && 
        this->threeFoldRep()) {
            this->result = "1/2-1/2";
            return "1/2-1/2";
        }
        
    
    if(this->whitePlayer->getRequireThreeFoldRep() && (!this->blackIsPlaying) && 
        this->threeFoldRep())  {
            this->result = "1/2-1/2";
            return "1/2-1/2";
        }
        
    if(this->deadPosition()) {
            this->result = "1/2-1/2";
            return "1/2-1/2";
    }
    return "*"; 

    

}

bool Game::playMove(bool black,int startX,int startY, int endX,int endY){
    if(black != this->blackIsPlaying) return false;
    std::pair<std::string,std::string> conf = board->getConfiguration();
    std::pair<bool,Move*> m; 
    if(black){
        m = this->blackPlayer->makeMove(this->board,startX, startY,endX,endY);
        if(m.second != NULL)  {
            m.second->setTurnId(this->numberOfMoves);
        this->numberOfMoves += 1;
        }
         
    }else{
        m = this->whitePlayer->makeMove(this->board,startX, startY,endX,endY);
        if(m.second != NULL)  m.second->setTurnId(this->numberOfMoves);
    }
    if(m.first) {
        this->moves.push_back(m.second);
        this->configurations.push_back(conf); 
        this->blackIsPlaying = !this->blackIsPlaying;
        return true; 
    }
    return false; 
}

void helpMenu() {
    char c; 
    system("clear"); 
    std::cout<<"|................................................."<<std::endl; 
    std::cout<<"|.......General rules to play this game"<<std::endl
        <<"|.......1.Moves: "<<std::endl
        <<"|...........Format: `C1R1 C2R2`"<<std::endl 
        <<"|...........Example: a1 a2, b8 c6, d2 d5 ."<<std::endl
        <<"|.......2.Pawn promotion: "<<std::endl
        <<"|...........When one of your pawns reach the enemy place, you'll choose the promotion !"<<std::endl
        <<"|....gameMenu.......Examples: Q for Queen, R for Rook, N for Knight"<<std::endl
        <<"|.......3.Resign:"<<std::endl
        <<"|...........If you want to resign, just type `resign` in your turn to play !"<<std::endl
        <<"|.......4.Draw:"<<std::endl
        <<"|...........To claim a draw : just type `CD` after you type your move !"<<std::endl
        <<"|...........Examples: a1 a3 CD, h1 g4 CD..."<<std::endl
        <<"|...........To ask for a draw : just type `AD` after you type your move !"<<std::endl
        <<"|...........Examples: a1 a3 AD, h1 g4 AD..."<<std::endl
        <<"|.......5.To stop the game:"<<std::endl
        <<"|...........Stop without save : type `STOP`"<<std::endl
        <<"|...........Stop and save: type `STOPSAVE`"<<std::endl
        <<"|.......6.To show this menu:"<<std::endl
        <<"|...........Type `HELP`"<<std::endl; 
    std::cout<<"|................................................."<<std::endl; 
    std::cout<<"Type anything to return Or start your game !"<<std::endl; 
        std::cin>>c;
    system("clear");  
}
// aux function ! 
bool verifyMove(std::string move ){
    if(move.size()>5) return false; 
    if(move[2] != ' ') return false; 
    int i = move[0] - 'a'; 
    if(i>7 || i <0) return false;
    i = move[1] - '1'; 
    if(i>7 || i <0) return false; 
    i = move[3] - 'a'; 
    if(i>7 || i <0) return false; 
    i = move[4] - '1'; 
    if(i>7 || i <0) return false; 
    return true; 
}
void Game::playGame() {
    helpMenu(); 
    system("clear");
    bool stop = false;
    int startX,startY,endX,endY; 
    bool done; 
    std::string result; 
    bool correctMove = false; 
    char promotion = ' ';
    //std::chrono::high_resolution_clock t_start; 
    //std::chrono::high_resolution_clock t_end; 
    std::string play = ""; 
    while(!stop) {
        this->getBoard()->printBoard(); 
        this->setBlackIsPlaying(false);
        result = this->getGameResult(); 
        if(this->result != "*" || this->result != "?") result = this->result; 
        if(result == "0-1") {
            stop = true; 
            std::cout<<"Black wins !"<<std::endl;
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        if(result == "1-0") {
            stop = true; 
            std::cout<<"White wins !"<<std::endl; 
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        if(result == "1/2-1/2") {
            stop = true; 
            std::cout<<"Game ended with a draw !"<<std::endl; 
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        correctMove = false; 
        auto t_start = std::chrono::high_resolution_clock::now();
        while(!correctMove) {
            correctMove = true;
            this->getWhitePlayer()->setAskForDraw(false);
            this->getWhitePlayer()->setRequireThreeFoldRep(false); 
            if(this->getBlackPlayer()->getAskForDraw()) {
                std::string answer = ""; 
                std::cout<<"White Player ask you for an agreement on Draw ? (N/y)  "<<std::endl;
                std::cin>>answer; 
                if(answer =="y") {
                    this->getBlackPlayer()->setAskForDraw(true); 
                    this->result = "1/2-1/2"; 
                    std::cout<<"Game ended with a draw !"<<std::endl; 
                    return; 
                }

            }
            std::cout<<"White player turn :"; 
                getline(std::cin >> std::ws, play); 
            if(play[play.size()-1] == 'D'){
                if(play[play.size()-2] == 'A') this->getWhitePlayer()->setAskForDraw(true);
                if(play[play.size()-2] == 'C') this->getWhitePlayer()->setRequireThreeFoldRep(true); 
                play.erase(play.size()-3,3); 
                std::cout<<"Your play"<<play<<std::endl; 
            } 
            if(play == "STOP") return; 
            if(play == "STOPSAVE") {
                this->saveGame(); 
                return; 
            }
            if(play == "HELP") {
                helpMenu();
                this->getBoard()->printBoard(); 
                std::cout<<"White player turn :";
                auto t_start = std::chrono::high_resolution_clock::now(); 
                getline(std::cin >> std::ws, play); 
            }
            if(play == "resign") {
                this->getWhitePlayer()->toResign();
            } else {

                startX = play[1] - '1'; 
                startY = play[0] - 'a'; 
                endX   = play[4] - '1'; 
                endY   = play[3] - 'a'; 
                if(verifyMove(play)) done = this->playMove(false,startX,startY,endX,endY); 
                else done = false; 
                if(!done) correctMove = false; 
                if(!correctMove) std::cout<<"wrong Move, please retype your move !"<<std::endl;
                if(this->moves[this->moves.size()-1]->getPieceType() == 'P') {
                    if(this->moves[this->moves.size()-1]->getEndX() == 7) {
                        std::cout<<"Please choose a promotion's type (`Q`,`R`,`N`) :";  
                        std::cin>>promotion; 
                        this->moves[this->moves.size()-1]->setPromotedTo(promotion); 
                        this->whitePlayer->pawnPromotion(this->board,promotion,this->moves[this->moves.size()-1]->getEndX(),this->moves[this->moves.size()-1]->getEndY()); 
                        system("clear"); 
                        this->board->printBoard(); 
                    }
                } 
            }
        } 

        auto t_end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds> (t_end-t_start);
        this->getClock()->decRemainingSecondsForWhite(duration);
        this->getClock()->incRemainingSecondsForWhite(this->getClock()->getClockInc());
        std::cout<<"Remaining time for white : "<<this->getClock()->getRemainingSecondsForWhite().count()<<" seconds"<<std::endl; 
        result = this->getGameResult(); 
        if(result == "0-1") {
            stop = true; 
            std::cout<<"Black wins !"<<std::endl;
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        if(result == "1-0") {
            stop = true; 
            std::cout<<"White wins !"<<std::endl; 
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        if(result == "1/2-1/2") {
            stop = true; 
            std::cout<<"Game ended with a draw !"<<std::endl; 
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        this->getBoard()->printBoard(); 
        this->setBlackIsPlaying(true);
        correctMove = false; 
         t_start = std::chrono::high_resolution_clock::now();
        while(!correctMove) {
            correctMove = true;
            this->getBlackPlayer()->setAskForDraw(false);
            this->getBlackPlayer()->setRequireThreeFoldRep(false);
            if(this->getWhitePlayer()->getAskForDraw()) {
                std::string answer = ""; 
                std::cout<<"White Player ask you for an agreement on Draw ? (N/y)  "<<std::endl;
                std::cin>>answer; 
                if(answer =="y") {
                    this->getBlackPlayer()->setAskForDraw(true); 
                    this->result = "1/2-1/2"; 
                    std::cout<<"Game ended with a draw !"<<std::endl; 
                    return; 
                }

            }

            std::cout<<"Black player turn :"; 
                getline(std::cin >> std::ws, play);

            if(play[play.size()-1] == 'D'){
                if(play[play.size()-2] == 'A') this->getBlackPlayer()->setAskForDraw(true);
                if(play[play.size()-2] == 'C') this->getBlackPlayer()->setRequireThreeFoldRep(true); 
                play.erase(play.size()-3,3); 
            } 
            if(play == "STOP") return; 
            if(play == "STOPSAVE") {
                this->saveGame(); 
                return; 
            }
            if(play == "HELP") {
                helpMenu();
                this->getBoard()->printBoard(); 
                std::cout<<"Black player turn :";
                auto t_start = std::chrono::high_resolution_clock::now(); 
                getline(std::cin >> std::ws, play); 
            }
            if(play == "resign") this->getBlackPlayer()->toResign();
            else{
                startX = play[1] - '1'; 
                startY = play[0] - 'a'; 
                endX   = play[4] - '1'; 
                endY   = play[3] - 'a';  
                if(verifyMove(play)) done = this->playMove(true,startX,startY,endX,endY); 
                else done = false;  
                if(!done) correctMove = false; 
                if(!correctMove) std::cout<<"wrong Move, please retype your move !"<<std::endl; 
                if(this->moves[this->moves.size()-1]->getPieceType() == 'P') {
                    if(this->moves[this->moves.size()-1]->getEndX() == 0) {
                        std::cout<<"Please choose a promotion's type (`Q`,`R`,`N`) :";  
                        std::cin>>promotion; 
                        this->moves[this->moves.size()-1]->setPromotedTo(promotion); 
                        this->blackPlayer->pawnPromotion(this->board,promotion,this->moves[this->moves.size()-1]->getEndX(),this->moves[this->moves.size()-1]->getEndY()); 
                        system("clear"); 
                        this->board->printBoard(); 
                    }
                } 
            }
        } 

         t_end = std::chrono::high_resolution_clock::now();
         duration = std::chrono::duration_cast<std::chrono::seconds> (t_end-t_start);
        this->getClock()->decRemainingSecondsForBlack(duration);
        this->getClock()->incRemainingSecondsForBlack(this->getClock()->getClockInc()); 
                std::cout<<"Remaining time for black : "<<this->getClock()->getRemainingSecondsForBlack().count()<<" seconds"<<std::endl; 
        result = this->getGameResult(); 
        if(result == "0-1") {
            stop = true; 
            std::cout<<"Black wins !"<<std::endl;
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        if(result == "1-0") {
            stop = true; 
            std::cout<<"White wins !"<<std::endl; 
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        if(result == "1/2-1/2") {
            stop = true; 
            std::cout<<"Game ended with a draw !"<<std::endl; 
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
    }
    char c;
    std::cout<<std::endl<<"Type any thing to continue ! "; 
    std::cin>>c; 
}

void Game::playAgainstAgent() {
    helpMenu(); 
    system("clear");
    bool stop = false;
    MinMaxPlayer* agent = new MinMaxPlayer(true);  
    int startX,startY,endX,endY; 
    bool done; 
    std::string result; 
    bool correctMove = false; 
    char promotion = ' ';
    //std::chrono::high_resolution_clock t_start; 
    //std::chrono::high_resolution_clock t_end; 
    std::string play = ""; 
    while(!stop) {
        this->getBoard()->printBoard(); 
        this->setBlackIsPlaying(false);
        result = this->getGameResult(); 
        if(this->result != "*" || this->result != "?") result = this->result; 
        if(result == "0-1") {
            stop = true; 
            std::cout<<"Black wins !"<<std::endl;
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        if(result == "1-0") {
            stop = true; 
            std::cout<<"White wins !"<<std::endl; 
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        if(result == "1/2-1/2") {
            stop = true; 
            std::cout<<"Game ended with a draw !"<<std::endl; 
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        correctMove = false; 
        auto t_start = std::chrono::high_resolution_clock::now();
        while(!correctMove) {
            correctMove = true;
            this->getWhitePlayer()->setAskForDraw(false);
            this->getWhitePlayer()->setRequireThreeFoldRep(false); 
            std::cout<<"White player turn :"; 
                getline(std::cin >> std::ws, play); 
            if(play[play.size()-1] == 'D'){
                if(play[play.size()-2] == 'C') this->getWhitePlayer()->setRequireThreeFoldRep(true); 
                play.erase(play.size()-3,3); 
                std::cout<<"Your play"<<play<<std::endl; 
            } 
            if(play == "STOP") return; 
            if(play == "STOPSAVE") {
                this->saveGame(); 
                return; 
            }
            if(play == "HELP") {
                helpMenu();
                this->getBoard()->printBoard(); 
                std::cout<<"White player turn :";
                auto t_start = std::chrono::high_resolution_clock::now(); 
                getline(std::cin >> std::ws, play); 
            }
            if(play == "resign") {
                this->getWhitePlayer()->toResign();
            } else {

                startX = play[1] - '1'; 
                startY = play[0] - 'a'; 
                endX   = play[4] - '1'; 
                endY   = play[3] - 'a'; 
                if(verifyMove(play)) done = this->playMove(false,startX,startY,endX,endY); 
                else done = false; 
                if(!done) correctMove = false; 
                if(!correctMove) std::cout<<"wrong Move, please retype your move !"<<std::endl;
                if(this->moves[this->moves.size()-1]->getPieceType() == 'P') {
                    if(this->moves[this->moves.size()-1]->getEndX() == 7) {
                        std::cout<<"Please choose a promotion's type (`Q`,`R`,`N`) :";  
                        std::cin>>promotion; 
                        this->moves[this->moves.size()-1]->setPromotedTo(promotion); 
                        this->whitePlayer->pawnPromotion(this->board,promotion,this->moves[this->moves.size()-1]->getEndX(),this->moves[this->moves.size()-1]->getEndY()); 
                        system("clear"); 
                        this->board->printBoard(); 
                    }
                } 
            }
        } 

        auto t_end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds> (t_end-t_start);
        this->getClock()->decRemainingSecondsForWhite(duration);
        this->getClock()->incRemainingSecondsForWhite(this->getClock()->getClockInc());
        std::cout<<"Remaining time for white : "<<this->getClock()->getRemainingSecondsForWhite().count()<<" seconds"<<std::endl; 
        result = this->getGameResult(); 
        if(result == "0-1") {
            stop = true; 
            std::cout<<"Black wins !"<<std::endl;
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        if(result == "1-0") {
            stop = true; 
            std::cout<<"White wins !"<<std::endl; 
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        if(result == "1/2-1/2") {
            stop = true; 
            std::cout<<"Game ended with a draw !"<<std::endl; 
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        system("clear"); 
        this->board->printBoard(); 
        this->setBlackIsPlaying(false);
        t_start = std::chrono::high_resolution_clock::now();
        agent->makeMove(this->getBoard());
        t_end = std::chrono::high_resolution_clock::now();
        system("clear"); 
        this->board->printBoard(); 
         duration = std::chrono::duration_cast<std::chrono::seconds> (t_end-t_start);
        this->getClock()->decRemainingSecondsForBlack(duration);
        this->getClock()->incRemainingSecondsForBlack(this->getClock()->getClockInc()); 
        std::cout<<"Remaining time for black : "<<this->getClock()->getRemainingSecondsForBlack().count()<<" seconds"<<std::endl; 
        result = this->getGameResult(); 
        if(result == "0-1") {
            stop = true; 
            std::cout<<"Black wins !"<<std::endl;
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        if(result == "1-0") {
            stop = true; 
            std::cout<<"White wins !"<<std::endl; 
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
        if(result == "1/2-1/2") {
            stop = true; 
            std::cout<<"Game ended with a draw !"<<std::endl; 
            char c;
            std::cout<<std::endl<<"Type any thing to continue ! "; 
            std::cin>>c;
            return; 
        }
         
    }
}
