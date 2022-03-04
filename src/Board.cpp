#include <iostream>
#include <fstream>
#include <string>
#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
using namespace std;
 
#define RESET   "\033[0m"
#define WHITE   "\033[5;47;30m"
#define CYAN    "\033[5;46;30m"
#define BLACK   "\033[5;40;37m"
#define GREEN   "\033[5;42;30m"


void Board::resetBoard(){
    for (int i=7; i>-1;i--) {
        vector<Spot> row; 
    bool black = true; 
    if(i == 0){
        row.push_back(Spot(new Rook(black),7-i,0,black)); 
        row.push_back(Spot(new Knight(black),7-i,1,black));
        row.push_back(Spot(new Bishop(black),7-i,2,!black)); 
        row.push_back(Spot(new Queen(black),7-i,3,!black));
        row.push_back(Spot(new King(black),7-i,4,black));
        row.push_back(Spot(new Bishop(black),7-i,5,black)); 
        row.push_back(Spot(new Knight(black),7-i,6,!black));
        row.push_back(Spot(new Rook(black),7-i,7,!black));
    }
    if(i == 7){
        row.push_back(Spot(new Rook(!black),7-i,0,!black)); 
        row.push_back(Spot(new Knight(!black),7-i,1,!black));
        row.push_back(Spot(new Bishop(!black),7-i,2,black)); 
        row.push_back(Spot(new Queen(!black),7-i,3,!black));
        row.push_back(Spot(new King(!black),7-i,4,black));
        row.push_back(Spot(new Bishop(!black),7-i,5,!black));
        row.push_back(Spot(new Knight(!black),7-i,6,black)); 
        row.push_back(Spot(new Rook(!black),7-i,7,black));
    }
    if((i == 1)||(i == 6)){
        row.push_back(Spot(new Pawn((i==1)),7-i,0,(i == 6))); 
        row.push_back(Spot(new Pawn((i==1)),7-i,1,!(i == 6))); 
        row.push_back(Spot(new Pawn((i==1)),7-i,2,(i == 6)));
        row.push_back(Spot(new Pawn((i==1)),7-i,3,!(i == 6)));
        row.push_back(Spot(new Pawn((i==1)),7-i,4,(i == 6)));
        row.push_back(Spot(new Pawn((i==1)),7-i,5,!(i == 6)));
        row.push_back(Spot(new Pawn((i==1)),7-i,6,(i == 6))); 
        row.push_back(Spot(new Pawn((i==1)),7-i,7,!(i == 6))); 
    }
    black = false; 
    if((i>1)&&(i<6)) {
        if((i == 2)||(i == 4)) black = !black; 
        for(int j=0;j<8;j++) {
            row.push_back(Spot(NULL,7-i,j,black));
            black=!black; 
        }
    }
    this->spots.push_back(row);
    }  
}
Spot* Board::getSpot(int x, int y){
    if((x>7)||(x<0)||(y>7)||(y<0)) {
        return NULL; 
    } 
    for(int i=0; i<8;i++) {
        for(int j=0; j<8; j++) {
            if(this->spots[i][j].getX() == x && this->spots[i][j].getY()== y) {
                return &(this->spots[i][j]);
            }
        }
    } 
    return  NULL; 
}
Board::Board()
{ 
    this->resetBoard(); 
}

Board::~Board()
{
}
void Board::printBoard() {
    if(this->unicode) this->printUnicode(); 
    else this->printBasic(); 
}
void Board::printBasic() 
{
        string spacing = "  ";    
        string color1="",color2="";
        string pieceColor = "b"; 
        cout<<spacing<<"A "<<spacing<<spacing<<"B "<<spacing<<spacing<<"C "<<spacing<<spacing<<"D "<<spacing
        <<spacing<<"E "<<spacing<<spacing<<"F "<<spacing<<spacing<<"G "<<spacing<<spacing<<"H "<<spacing<<endl;   
        for(int i=7; i>-1;i--) {
                if((i)%2) {
                    color1 = WHITE; 
                    color2 = GREEN; 
                }else{
                    color2 = WHITE; 
                    color1 = GREEN; 
                }
                for(int k=0;k<3;k++) {
                    int j = 0; 
                    while(j<8) {
                        if(k==1) {
                            if((this->spots[i][j].getPiece() != NULL)) {
                                if(this->spots[i][j].getPiece()->isBlack()) pieceColor = "b"; 
                                else pieceColor = "w"; 
                                cout<<color1<<spacing<<pieceColor<<this->spots[i][j].getPiece()->getType()<<spacing<<RESET;
                                
                            } else{
                                cout<<color1<<spacing<<"  "<<spacing<<RESET;
                            }
                            
                            if((this->spots[i][j+1].getPiece() != NULL)) {
                                if(this->spots[i][j+1].getPiece()->isBlack()) pieceColor = "b"; 
                                else pieceColor = "w"; 
                                cout<<color2<<spacing<<pieceColor<<this->spots[i][j+1].getPiece()->getType()<<spacing<<RESET; 
                            }
                            else{
                                cout<<color2<<spacing<<"  "<<spacing<<RESET;
                            }
                            
                        }else {
                            cout<<color1<<spacing<<"  "<<spacing<<RESET;
                            cout<<color2<<spacing<<"  "<<spacing<<RESET;
                        }
                        j+=2; 
                    }
                    if(k==1) cout<<"   "<<i+1<<endl;
                    else cout<<endl;  
                }
        } 
    cout<<spacing<<"A "<<spacing<<spacing<<"B "<<spacing<<spacing<<"C "
    <<spacing<<spacing<<"D "<<spacing<<spacing<<"E "<<spacing<<spacing<<"F "<<spacing<<spacing<<"G "<<spacing<<spacing<<"H  "<<endl;
}
void Board::printUnicode() {
        string spacing = "  ";    
        string color1="",color2=""; 
        cout<<spacing<<"A "<<spacing<<spacing<<"B "<<spacing<<spacing<<"C "<<spacing<<spacing<<"D "<<spacing
        <<spacing<<"E "<<spacing<<spacing<<"F "<<spacing<<spacing<<"G "<<spacing<<spacing<<"H "<<spacing<<endl;
        
        for(int i=7; i>-1;i--) {
                if((i)%2) {
                    color1 = WHITE; 
                    color2 = GREEN; 
                }else{
                    color2 = WHITE; 
                    color1 = GREEN; 
                }
                for(int k=0;k<3;k++) {
                    int j = 0; 
                    while(j<8) {
                        if(k==1) {
                            if((this->spots[i][j].getPiece() != NULL)) {
                                cout<<color1<<spacing<<" "<<this->spots[i][j].getPiece()->getPrintedValue()<<spacing<<RESET;
                                
                            } else{
                                cout<<color1<<spacing<<"  "<<spacing<<RESET;
                            }
                            
                            if((this->spots[i][j+1].getPiece() != NULL)) {
                                cout<<color2<<spacing<<" "<<this->spots[i][j+1].getPiece()->getPrintedValue()<<spacing<<RESET; 
                            }
                            else{
                                cout<<color2<<spacing<<"  "<<spacing<<RESET;
                            }
                            
                        }else {
                            cout<<color1<<spacing<<"  "<<spacing<<RESET;
                            cout<<color2<<spacing<<"  "<<spacing<<RESET;
                        }
                        j+=2; 
                    }
                    if(k==1) cout<<"   "<<i+1<<endl;
                    else cout<<endl;  
                }
        } 
    cout<<spacing<<"A "<<spacing<<spacing<<"B "<<spacing<<spacing<<"C "
    <<spacing<<spacing<<"D "<<spacing<<spacing<<"E "<<spacing<<spacing<<"F "<<spacing<<spacing<<"G "<<spacing<<spacing<<"H  "<<endl;
}

vector<Piece*>Board::getKilledPieces(bool isBlack){
    if(isBlack){
        return this->killedBlackPieces; 
    }
    return this->killedWhitePieces; 
}
void Board::killPiece(Piece* p){
    if(p->isBlack()) this->killedBlackPieces.push_back(p); 
    else this->killedWhitePieces.push_back(p); 
}
std::pair<int,int> Board::getPiecePosition(bool black,char type,int sX,int sY,char column, char row) {
    int x=0,y=0; 
    Spot* s = this->getSpot(sX,sY);
    Piece* p = NULL;  
    if(column == ' ' && row == ' '){
        for(int i=0; i<8;i++) {
            for(int j=0;j<8;j++){
                p = this->getSpot(i,j)->getPiece(); 
                if(p != NULL) {
                if(p->isBlack() == black) { 
                    if(p->getType() == type){
                        
                        if(p->canMove(this,this->getSpot(i,j),s) == 1){
                            //std::cout<<i<<" - "<<j<<" - "<<p->canMove(this,this->getSpot(i,j),s)<<std::endl;
                            x = i; y = j; 
                        }  
                    }
                }
                }
            }
        }
    }else{
        if(column != ' '){
            int j = column - 'a'; 
            for(int i=0; i<8;i++) {
                p = this->getSpot(i,j)->getPiece();
                if(p != NULL) {
                    if(p->isBlack() == black) { 
                        if(p->getType() == type){
                            
                            if(p->canMove(this,this->getSpot(i,j),s) == 1){
                                
                                //std::cout<<i<<" - "<<j<<" - "<<p->canMove(this,this->getSpot(i,j),s)<<std::endl;
                                x = i; y = j; 
                            }  
                        }
                    }
                }
            }
        }else{
            int i = row - '1'; 
            for(int j=0; j<8;j++) {
                p = this->getSpot(i,j)->getPiece();
                if(p != NULL) {
                    if(p->isBlack() == black) { 
                        if(p->getType() == type){
                            if(p->canMove(this,this->getSpot(i,j),s) == 1){
                                //std::cout<<i<<" - "<<j<<" - "<<p->canMove(this,this->getSpot(i,j),s)<<std::endl;
                                x = i; y = j; 
                            }  
                        }
                    }
                }            
            }
        }
    }
    return std::pair<int,int>(x,y); 
}
bool Board::copyBoard(Board* copy){
    *copy = *this;
    return true; 
}
bool Board::setConfiguration(std::pair<std::string,std::string> conf) {

    this->resetEmptyBoard(); 
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
    std::string word = conf.first; 
    std::string token=""; 
    Piece* p =NULL; 
    bool stop=false;
    int i,j;  
    while(!stop) {
        if(word.size() == 0) stop = true;
        else {
            token = word.substr(0,word.find(" "));
            word.erase(0,word.find(" ")+1); 
            i = token[2] - '1'; 
            j = token[1] - 'a';   
            switch(token[0]){
            case 'P':
                p = new Pawn(false);
                if(token.size() == 4) {
                    i = token[3] - '1'; 
                    j = token[2] - 'a'; 
                    ((Pawn*)p)->setMoved(true); 
                }
                else ((Pawn*)p)->setMoved(false);
                whitePawns --; 
            break;
            case 'Q':
                p = new Queen(false);  
                whiteQueen--; 
            break;
            case 'R':
                p = new Rook(false); 
                whiteRooks--; 
            break; 
            case 'N':
                p = new Knight(false); 
                whiteKnights--; 
            break;
            case 'B':
                p = new Bishop(false);
                whiteBishops--; 
            break;
            case 'K':
                p = new King(false); 
            break; 
            default:
                std::cerr<<"Format not recognized !! "<<token[0]<<std::endl; 
                return false;
            break; 
            }
            if(this->getSpot(i,j)->isOccupied()) {
                this->printBoard(); 
                std::cerr<<"Format not recognized !! "<<i<<j<<token<<std::endl; 
                return false;
            }
            this->getSpot(i,j)->setOccupied(true); 
            this->getSpot(i,j)->setPiece(p); 
        } 
    }
    stop = false; 
    
    word = conf.second;  // black configuration 
    while(!stop) {
        if(word.size() == 0) stop = true;
        else {
            token = word.substr(0,word.find(" "));
            word.erase(0,word.find(" ")+1); 
            i = token[2] - '1'; 
            j = token[1] - 'a';  
            switch(token[0]){
            case 'P':
                p = new Pawn(true);
                if(token.size() == 4) {
                    i = token[3] - '1'; 
                    j = token[2] - 'a'; 
                    ((Pawn*)p)->setMoved(true); 
                } 
                else ((Pawn*)p)->setMoved(false);
                blackPawns --; 
            break;
            case 'Q':
                p = new Queen(true);  
                blackQueen--; 
            break;
            case 'R':
                p = new Rook(true); 
                blackRooks--; 
            break; 
            case 'N':
                p = new Knight(true); 
                blackKnights--; 
            break;
            case 'B':
                p = new Bishop(true);
                blackBishops--; 
            break;
            case 'K':
                p = new King(true); 
            break; 
            default:
                std::cerr<<"Format not recognized !!"<<std::endl; 
                return false;
            break; 
            }
            if(this->getSpot(i,j)->isOccupied()) {
                std::cerr<<"Format not recognized !!"<<std::endl; 
                return false;
            }
            this->getSpot(i,j)->setOccupied(true); 
            this->getSpot(i,j)->setPiece(p); 
        } 
    }
    while(whitePawns>0) {
        whitePawns--; 
        p = new Pawn(false); 
        this->killedWhitePieces.push_back(p); 
    }
    while(blackPawns>0) {
        blackPawns--; 
        p = new Pawn(false); 
        this->killedBlackPieces.push_back(p); 
    }
    while(whiteBishops>0) {
        whiteBishops--; 
        p = new Bishop(false); 
        this->killedWhitePieces.push_back(p); 
    }
    while(blackBishops>0) {
        blackBishops--; 
        p = new Bishop(false); 
        this->killedBlackPieces.push_back(p); 
    }
    while(whiteKnights>0) {
        whiteKnights--; 
        p = new Knight(false); 
        this->killedWhitePieces.push_back(p); 
    }
    while(blackKnights>0) {
        blackKnights--; 
        p = new Knight(false); 
        this->killedBlackPieces.push_back(p); 
    }
    while(whiteRooks>0) {
        whiteRooks--; 
        p = new Rook(false); 
        this->killedWhitePieces.push_back(p); 
    }
    while(blackRooks>0) {
        blackRooks--; 
        p = new Rook(false); 
        this->killedBlackPieces.push_back(p); 
    }
    if(whiteQueen>0) this->killedWhitePieces.push_back(new Queen(false));
    if(blackQueen>0) this->killedBlackPieces.push_back(new Queen(true));
    return true;  
}
std::pair<std::string,std::string> Board::getConfiguration() {
    Piece* p; 
    std::string black = ""; 
    std::string white = ""; 
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            p = this->getSpot(i,j)->getPiece(); 
            if(p!=NULL) {
                if(p->isBlack()){
                    black+=p->getType(); 
                    if(p->getType() == 'P') {
                       // if(((Pawn*)p)->getMoved()) black+='E'; 
                    }
                    black+=char(j+'a');
                    black+=char(i+'1'); 
                    black+=" "; 
                }else{
                    white+=p->getType(); 
                    if(p->getType() == 'P') {
                        // if(((Pawn*)p)->getMoved()) black+='E'; 
                    }
                    white+=char(j+'a');
                    white+=char(i+'1'); 
                    white+=" ";                     
                }
            }
        }
    }
    return std::pair<std::string,std::string> (white,black); 
}
void Board::saveConfiguration(std::string file){
    std::ofstream saveFile;
    saveFile.open(file); 
    if( !saveFile ) { // file couldn't be opened
        std::cerr << "Error: file could not be opened" << std::endl;
        exit(1);
    }
    std::pair<std::string,std::string> conf = this->getConfiguration(); 
    saveFile<<conf.first<<"\n";
    saveFile<<conf.second<<"\n";  
    saveFile.close(); 
}
bool Board::readConfiguration(std::string file){
    std::ifstream srcFile; 
    srcFile.open(file);
    if( !srcFile ) { // file couldn't be opened
        std::cerr << "Error: file could not be opened" << std::endl;
        return false; 
    }
    this->resetEmptyBoard(); 
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
    std::string word="";
    std::string token=""; 
    Piece* p =NULL; 
    std::getline(srcFile,word); // white configuration 
    bool stop=false;
    int i,j; 
    while(!stop) {
        if(word.size() == 0) stop = true;
        else {
            token = word.substr(0,word.find(" "));
            word.erase(0,word.find(" ")+1); 
            i = token[2] - '1'; 
            j = token[1] - 'a';  
            switch(token[0]){
            case 'P':
                p = new Pawn(false);
                if(token.size() == 4) {
                    i = token[3] - '1'; 
                    j = token[2] - 'a'; 
                    ((Pawn*)p)->setMoved(true); 
                }
                else ((Pawn*)p)->setMoved(false);
                whitePawns --; 
            break;
            case 'Q':
                p = new Queen(false);  
                whiteQueen--; 
            break;
            case 'R':
                p = new Rook(false); 
                whiteRooks--; 
            break; 
            case 'N':
                p = new Knight(false); 
                whiteKnights--; 
            break;
            case 'B':
                p = new Bishop(false);
                whiteBishops--; 
            break;
            case 'K':
                p = new King(false); 
            break; 
            default:
                std::cerr<<"Format not recognized !! "<<token[0]<<std::endl; 
                return false;
            break; 
            }
            if(this->getSpot(i,j)->isOccupied()) {
                this->printBoard(); 
                std::cerr<<"Format not recognized !! "<<i<<j<<token<<std::endl; 
                return false;
            }
            this->getSpot(i,j)->setOccupied(true); 
            this->getSpot(i,j)->setPiece(p); 
        } 
    }
    stop = false; 
    
    std::getline(srcFile,word); // black configuration 
    while(!stop) {
        if(word.size() == 0) stop = true;
        else {
            token = word.substr(0,word.find(" "));
            word.erase(0,word.find(" ")+1); 
            i = token[2] - '1'; 
            j = token[1] - 'a';  
            switch(token[0]){
            case 'P':
                p = new Pawn(true);
                if(token.size() == 4) {
                    i = token[3] - '1'; 
                    j = token[2] - 'a'; 
                    ((Pawn*)p)->setMoved(true); 
                } 
                else ((Pawn*)p)->setMoved(false);
                blackPawns --; 
            break;
            case 'Q':
                p = new Queen(true);  
                blackQueen--; 
            break;
            case 'R':
                p = new Rook(true); 
                blackRooks--; 
            break; 
            case 'N':
                p = new Knight(true); 
                blackKnights--; 
            break;
            case 'B':
                p = new Bishop(true);
                blackBishops--; 
            break;
            case 'K':
                p = new King(true); 
            break; 
            default:
                std::cerr<<"Format not recognized !!"<<std::endl; 
                return false;
            break; 
            }
            if(this->getSpot(i,j)->isOccupied()) {
                std::cerr<<"Format not recognized !!"<<std::endl; 
                return false;
            }
            this->getSpot(i,j)->setOccupied(true); 
            this->getSpot(i,j)->setPiece(p); 
        } 
    }
    while(whitePawns>0) {
        whitePawns--; 
        p = new Pawn(false); 
        this->killedWhitePieces.push_back(p); 
    }
    while(blackPawns>0) {
        blackPawns--; 
        p = new Pawn(false); 
        this->killedBlackPieces.push_back(p); 
    }
    while(whiteBishops>0) {
        whiteBishops--; 
        p = new Bishop(false); 
        this->killedWhitePieces.push_back(p); 
    }
    while(blackBishops>0) {
        blackBishops--; 
        p = new Bishop(false); 
        this->killedBlackPieces.push_back(p); 
    }
    while(whiteKnights>0) {
        whiteKnights--; 
        p = new Knight(false); 
        this->killedWhitePieces.push_back(p); 
    }
    while(blackKnights>0) {
        blackKnights--; 
        p = new Knight(false); 
        this->killedBlackPieces.push_back(p); 
    }
    while(whiteRooks>0) {
        whiteRooks--; 
        p = new Rook(false); 
        this->killedWhitePieces.push_back(p); 
    }
    while(blackRooks>0) {
        blackRooks--; 
        p = new Rook(false); 
        this->killedBlackPieces.push_back(p); 
    }
    if(whiteQueen>0) this->killedWhitePieces.push_back(new Queen(false));
    if(blackQueen>0) this->killedBlackPieces.push_back(new Queen(true));
    return true; 

}
void Board::setUnicode(bool u){this->unicode = u;}
void Board::resetEmptyBoard() {
    for(int i=0; i<8; i++) {
        for(int j=0; j<8;j++){
            this->getSpot(i,j)->setOccupied(false); 
            this->getSpot(i,j)->setPiece(NULL); 
        }
    }
    this->killedBlackPieces.clear(); 
    this->killedWhitePieces.clear(); 
}