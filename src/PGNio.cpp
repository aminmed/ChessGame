#include "PGNio.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
PGNio::PGNio(std::string file, bool readOnly)
{
    this->filePath = file;
    this->readOnly = readOnly; 
}

PGNio::~PGNio()
{
}
void PGNio::setResult(std::string result) {this->result = result;}
void PGNio::setHeaders(std::vector<std::pair<std::string,std::string>> headers) {this->headers = headers;}
std::string PGNio::getResult() {
    for(int i=0; i<this->headers.size();i++) {
        if(this->headers[i].first == "Result") {
            return this->headers[i].second; 
        }
    }
    return "?"; 
}
std::string PGNio::getBlackPlayerName() {
    for(int i=0; i<this->headers.size();i++) {
        if(this->headers[i].first == "Black") {
            return this->headers[i].second; 
        }
    }
    return "?"; 
    return "?"; 
}
std::string PGNio::getWhitePlayerName() {
    for(int i=0; i<this->headers.size();i++) {
        if(this->headers[i].first == "White") {
            return this->headers[i].second; 
        }
    }
    return "?"; 
}
bool PGNio::resetMoves(){
    for(int i=0; i<this->moves.size(); i++) {
        delete (this->moves[i]);  
    }
    this->moves.clear(); 
    return true; 
} 

// PNG Format settings : 
bool PGNio::writeMovesToPGN(std::string file) 
{
    std::ofstream pgnFile; 
    pgnFile.open(file);
    if( !pgnFile ) { // file couldn't be opened
      std::cerr << "Error: file could not be opened" << std::endl;
      exit(1);
    }

    int turnId = 0;
    int prev_turnId = -1;  
    std::string word= ""; 
    for(int j=0; j<this->headers.size();j++) {
        pgnFile<<"["<<this->headers[j].first<<" "<<"\""<<this->headers[j].second<<"\"]"<<std::endl; 
    }
    pgnFile<<"\n"; 
    for(int i = 0; i < this->moves.size(); i++) {
        word=""; 
        turnId = this->moves[i]->getTurnId(); 
        if(turnId != prev_turnId) {
            pgnFile<<turnId<<". ";
            prev_turnId = turnId; 
        }
        if(this->moves[i]->getStart() == "O-O-O")
        {
            pgnFile<<"O-O-O "; 
        }else{
            if(this->moves[i]->getStart() == "O-O") pgnFile<<"O-O ";
            else{
                if(this->moves[i]->getPieceType() != 'P'){
                    word+=this->moves[i]->getPieceType(); 
                }
                word+=this->moves[i]->getStart(); 
                if(this->moves[i]->getCaptering()) {
                    word+="x"; 
                }
                word+=this->moves[i]->getEnd(); 
                if(this->moves[i]->getPromotedTo() != ' '){
                    word+="=";
                    word+=this->moves[i]->getPromotedTo(); 
                }
                if(turnId%5 == 0) word+="\n"; 
                    pgnFile<<word<<" "; 
                 }
        }

    }
    pgnFile<<this->getResult();
    pgnFile.close(); 
    return true; 
}
std::pair<std::string,std::string> PGNio::extractHeaderData(std::string header) {
    header.erase(0,1); // delete the first '[' 
    std::string headerName = header.substr(0, header.find(" ")); 
    header.erase(0, header.find(" ") + 2); 
    std::string headerValue = header.substr(0, header.find("\""));
    return std::pair<std::string,std::string>(headerName,headerValue); 
}

Move* PGNio::extractMove(bool black,Board* board,std::string step){
    bool captering = false;
    int x, y; 
    Move* m =NULL; 
    std::string start = "a1"; 
    std::string end = "a1";

    char type = step[0];
    char column = ' '; 
    char row = ' '; 
    if(type < 'Z') 
    {
        step.erase(0,1); //remove piece type as it is not pawn        
    }
    else {
        type = 'P';
    }
    if(step.length()>=3 && step[step.length()-3] == 'x') { // step has the format x|column|row
        captering = true;
        step.erase(step.length()-3,1); 
        
    }
    
    if(step.length() >= 3) { // step could have the format column|x|column|row or row|x|column|row or column|row|x|column|row
        column = step[0]; 
        if(column - '1' <= 9) {
            row = column; 
            column = ' '; 
            step.erase(0,1);
        }else {
            step.erase(0,1);
            if(step.length() >= 3){
                row = step[0]; 
                step.erase(0,1);
            }
        }
        
    }
    y = step[0] - 'a'; 
    x = step[1] - '1'; 
    std::pair<int,int> xy= board->getPiecePosition(black,type,x,y,column,row);
    end[0] = step[0]; 
    end[1] = step[1];
    start[1] = xy.first + '1'; 
    start[0] = xy.second + 'a';
    return new Move(this->turns+1,start,end,captering,type); 
}
std::string PGNio::removeComments(std::string w) {
        // remove comments symboles ! + ? -  
    bool comments = true; 
    while (comments)
    {
        if((w[w.length()-1]=='!')||(w[w.length()-1]=='?')||
            (w[w.length()-1]=='+')||(w[w.length()-1]=='-')||
            (w[w.length()-1]=='#') || (w[w.length()-1]=='=')) {
            w.erase(w.length()-1,1); 
            comments = true; 
        }else comments = false; 
    }
    return w;  
}


Board* PGNio::readMovesFromPGN(int turnId) {
    // starting chess board : 
    std::string file = this->filePath; 
    Board* board = new Board(); 
    bool done = false; 
    //open the file in read mode    
    std::ifstream pgnFile; 
    pgnFile.open(file);
    if( !pgnFile ) { // file couldn't be opened
      std::cerr << "Error: file could not be opened" << std::endl;
      exit(1);
    }
    //headers : we consider only the first's 7 headers in the PGN file
    std::string line; 
    int headers = 0; 
    char c; 
    Player* player1 = new Player(true,""); Player* player2 = new Player(false,"");  
    std::getline(pgnFile,line); 
    while(line.size() != 0) {
        this->headers.push_back(extractHeaderData(line));   
        if(this->headers[this->headers.size()-1].first == "black") 
        {
            player1->setName(this->headers[this->headers.size()-1].second); 
        }
        if(this->headers[this->headers.size()-1].first == "white") {
            player2->setName(this->headers[this->headers.size()-1].second); 
        }   
        std::getline(pgnFile,line);
    } 
    // extracting moves from file PNG 
    std::string w0,w1,w2;
    Move *move = NULL; 
    char promotionType; 
    bool thereIsPromotion = false; 
    Spot* start = NULL; Spot* end = NULL; 
    while (pgnFile >> w0)
    {   
        thereIsPromotion = false; 
        if(w0.find("-") > w0.length()) {
            pgnFile >> w1;
            w1 = removeComments(w1); 
            // if w read contain = means there is promotion to the moved piece
            if(w1.find("=") < w1.length()) {
                thereIsPromotion = true;
                promotionType = w1[w1.length()-1]; 
                w1.erase(w1.length()-2,2); 
            }
            // king side rook 
            if(w1 == "O-O") {
                player2->casteling(board,true);
                move = new Move(this->turns+1,"O-O","O-O",false,'K');
            }else{
                // Queen side rook 
               if(w1 == "O-O-O") {
                   done =  player2->casteling(board,false);
                    move = new Move(this->turns+1,"O-O-O","O-O-O",false,'K');
               }else{
                    if(w1.find("-") < w1.length()) {
                        this->result = w1;
                        pgnFile.close();
                        return board;
                    }
                    move = this->extractMove(false,board,w1); 
                    done = (player2->makeMove(board,move->getStartX(),move->getStartY(),move->getEndX(),move->getEndY())).first;
                    if(thereIsPromotion) {
                        move->setPromotedTo(promotionType); 
                        player2->pawnPromotion(board,promotionType,move->getEndX(),move->getEndY()); 
                    }  
               }
            }
            this->moves.push_back(move);
            if(done ==false) {
                std::cout<<this->turns<<" - "<<std::endl;
                std::cout<<"Error in reading PGN file provided"<<std::endl; 
                pgnFile.close();
                board->printBoard();  
                std::cin>>c; 
            }
            thereIsPromotion = false;
            pgnFile >> w2; 
            w2 = removeComments(w2); 
            // if w read contain = means there is promotion to the moved piece 
            if(w2.find("=") < w2.length()) {
                thereIsPromotion = true;
                promotionType = w2[w2.length()-1]; 
                w2.erase(w2.length()-2,2); 
            } 
            // King side rook 
            if(w2 == "O-O") {
                done = player1->casteling(board,true);
                move = new Move(this->turns+1,"O-O","O-O",false,'K'); 
            }else{
                // Queen side rook 
               if(w2 == "O-O-O") {
                   done =  player1->casteling(board,false);
                    move = new Move(this->turns+1,"O-O-O","O-O-O",false,'K');
               }else{
                    if(w2.find("-") < w2.length()){
                        this->result = w2; 
                        pgnFile.close();
                        return board;
                    }

                    move = this->extractMove(true,board,w2);  
                    done = (player1->makeMove(board,move->getStartX(),move->getStartY(),move->getEndX(),move->getEndY())).first;
                    // pawn promotion 
                    if(thereIsPromotion) {
                        move->setPromotedTo(promotionType); 
                        player1->pawnPromotion(board,promotionType,move->getEndX(),move->getEndY()); 
                    }    
               }
            }
            this->turns = std::stoi(w0.substr(0, w0.find(".")));
            if(this->turns == turnId && turnId >0) {
                    this->result = "*"; 
                    pgnFile.close();
                    return board;
            }
            this->moves.push_back(move); 
            if(done ==false) {
                std::cout<<this->turns<<std::endl; 
                std::cout<<"Error in reading PGN file provided"<<std::endl;
                pgnFile.close();
                board->printBoard();  
                std::cin>>c; 
            }
           if(this->readOnly) {
               system("clear");
               board->printBoard();
               std::cout<<"Turn "<<this->turns<<std::endl; 
               sleep(1); 
           }
        }
        else {
            // end of file !!! : 
            this->result = w0; 
        }
 
    }
    pgnFile.close();
    return board; 
}
std::string PGNio::getFileName() {
    return this->filePath; 
}
Move* PGNio::getMoveById(int i) {
    return this->moves[i]; 
}
void PGNio::addMove(Move* move){ 
    this->moves.push_back(move); 
}