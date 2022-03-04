#include "Player.h"
#include "King.h"
#include "Rook.h"
#include "Pawn.h"
#include "Queen.h"
#include "Knight.h"

Player::Player(bool black,std::string name)
{
    this->black = black; 
    this->name  = name; 
}
std::string Player::getName(){
    return this->name; 
}
void Player::toResign() {
        this->resign = true; 
}
bool Player::isResigned() {
        return this->resign; 
}
void Player::setAskForDraw(bool ask){this->askForDraw = ask;}
bool Player::getAskForDraw(){return this->askForDraw;}
bool Player::getRequireThreeFoldRep(){
    return this->requireThreeFoldRep; 
}
void Player::setRequireThreeFoldRep(bool require) {
    this->requireThreeFoldRep = require; 
}
bool Player::staleMate(Board* board){
    if(this->check(board)) return false;
    Spot* start = NULL;  
    Spot* end = NULL; 
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            start = board->getSpot(i,j); 
            if(start->getPiece() != NULL) {
                if(start->getPiece()->isBlack() == this->isBlack()) 
                {
                    for(int x=0; x<8;x++){
                        for(int y=0;y<8; y++){
                            end = board->getSpot(x,y); 
                            if(start->getPiece()->canMove(board,start,end) && this->safeMove(board,start,end)) {
                                return false; 
                            }
                        }
                    }
                }
            }
        }
    }
    return  true; 
}
void Player::setName(std::string name) {this->name = name; }
Player::~Player(){}
bool Player::isBlack() {return this->black;}

bool Player::pawnPromotion(Board *board,char type, int pawnX, int pawnY){
    Piece* p = board->getSpot(pawnX,pawnY)->getPiece(); 
    if(p == NULL) return false;
    if(p->getType() != 'P') return false;  
    if(p->isBlack() != this->isBlack()) return false; 
    if(pawnX != (!this->isBlack())*7) return false; 
    p->~Piece(); 
    switch(type){
        case 'Q':
        p = new Queen(this->isBlack()); 
        break;
        case 'R':
        p = new Rook(this->isBlack());
        break;
        case 'N':
        p = new Knight(this->isBlack()); 
        break; 
        default: return false; 
        break; 
    }
    board->getSpot(pawnX,pawnY)->setPiece(p); 
    board->getSpot(pawnX,pawnY)->setOccupied(true); 
    return true; 

}
bool Player::casteling(Board *board,bool KingsRook){
    King* k; 
    Rook* r; 
    if(this->check(board)) return false; 
    k = (King*)board->getSpot(this->black*7,4)->getPiece(); 
    r = (Rook*)board->getSpot(this->black*7,KingsRook*7)->getPiece();
    if(k == NULL || r == NULL) return false; 
    if(k->isMoved() || r->isMoved()) return false; 
    int interY = 4; 
    int step = (KingsRook) ? 1:-1; 
    interY+=step;  
    while(interY!=KingsRook*7) {
        if(board->getSpot(this->black*7,interY)->getPiece() != NULL) return false; 
        interY+=step; 
    }
    board->getSpot(this->black*7,4)->setPiece(NULL); 
    board->getSpot(this->black*7,KingsRook*7)->setPiece(NULL);
    board->getSpot(this->black*7,KingsRook*7)->setOccupied(false);
    board->getSpot(this->black*7,4)->setOccupied(false); 
    if(KingsRook) {
        board->getSpot(this->black*7,6)->setPiece(k);
        board->getSpot(this->black*7,6)->setOccupied(true);
        board->getSpot(this->black*7,5)->setPiece(r);
        board->getSpot(this->black*7,5)->setOccupied(true);
    }
    else  {
        board->getSpot(this->black*7,2)->setPiece(k);
        board->getSpot(this->black*7,2)->setOccupied(true);
        board->getSpot(this->black*7,3)->setPiece(r);
        board->getSpot(this->black*7,3)->setOccupied(true);
    }

    return true; 
}
bool Player::safeMove(Board* board ,Spot* start, Spot* end) {
    Piece* piece =start->getPiece();  
    Piece* pieceToKill = NULL; 
    bool safe = true; 
    if(piece == NULL) return false; 
    if(piece->canMove(board,start,end)){
            pieceToKill = NULL; 
            if(end->isOccupied()) {
                pieceToKill = end->getPiece(); 
            }
            end->setPiece(piece); 
            end->setOccupied(true); 
            start->setPiece(NULL); 
            start->setOccupied(false); 
            if(this->check(board)) {
                safe = false; 
            }
            // back play the move played !  
            start->setPiece(piece); 
            end->setPiece(pieceToKill); 
            start->setOccupied(true); 
            end->setOccupied((pieceToKill!=NULL)); 
        return safe; 
    }
    return false; 
}
bool Player::check(Board *board){
    // find the king of the player ! 
    Piece* piece; 
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            piece = board->getSpot(i,j)->getPiece(); 
            if(piece != NULL) {
                if(piece->getType() == 'K' && piece->isBlack() == this->isBlack()) {
                    return ((King*)piece)->isThreatened(board); 
                }
            }
        }
    }
    return true; 
}
bool Player::canSaveKing(Board* board, int startX, int startY) {
    Piece* piece =board->getSpot(startX,startY)->getPiece();  
    Piece* pieceToKill = NULL; 
    bool saved = false; 
    if(piece == NULL) return false; 
    if(piece->isBlack() != this->black) return false; 
     
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) { 
            if(piece->canMove(board,board->getSpot(startX,startY),board->getSpot(i,j))){ 
               Spot* start=board->getSpot(startX,startY); Spot* end=board->getSpot(i,j); 
               pieceToKill = NULL; 
               if(end->isOccupied()) {
                   pieceToKill = end->getPiece(); 
               }
               end->setPiece(piece); 
               end->setOccupied(true); 
               start->setPiece(NULL); 
               start->setOccupied(false); 
               if(this->check(board) == false) {
                   saved = true; 
                   
                }
                // back play the move played !  
                start->setPiece(piece); 
                end->setPiece(pieceToKill); 
                start->setOccupied(true); 
                end->setOccupied((pieceToKill!=NULL)); 
            }
        }
    }
    return saved; 
}
bool Player::checkMate(Board *board) {
    if(this->check(board)) {
        for(int i=0; i<8; i++) {
            for(int j=0; j<8; j++) {
                if(board->getSpot(i,j)->getPiece() != NULL) {
                    if(this->canSaveKing(board,i,j)) return false; 
                }
            }
        }
        return true; 
    }
    return false;  
}

std::pair<bool,Move*> Player::makeMove(Board *board,int startX,int startY, int endX, int endY){
    
    Spot *start = board->getSpot(startX,startY);
    Spot *end = board->getSpot(endX,endY); 
    Piece *piece = start->getPiece(); 
    
    Move* m = NULL; 

    std::string startString= "";
    startString+=char(start->getY()+'a'); 
    startString+=char(start->getX()+'1'); 
    std::string endString= "";
    endString+= char(end->getY()+'a'); 
    endString+= char (end->getX()+'1'); 

    if(start->isOccupied() && (start->getPiece()->isBlack() == this->isBlack() )) 
    {
        if(start->getPiece()->canMove(board,start,end)){
            //// making a move :
            // verify that the king will not be in danger after the move 
           if(this->safeMove(board,start,end)==false) return std::pair<bool,Move*>(false,NULL);  
            // find out if an en passant is possible if the piece to move is pawn
            
            m = new Move(0,startString,endString,false,start->getPiece()->getType()); 
            if(start->getPiece()->getType() == 'P'){
                // if the pawn is moved already two squares 
                if(((Pawn*)start->getPiece())->getMoved()){
                    ((Pawn*)start->getPiece())->setMoved(false);
                }
                // if the pawn is moving two squares for first time ! 
                if(startX == endX + 2 || startX == endX -2) {
                   ((Pawn*)start->getPiece())->setMoved(true); 
                }
                if(start->getY() != end->getY()){
                   if(end->getPiece() == NULL){
                       //en passant case !! 
                       piece = board->getSpot(startX,endY)->getPiece();
                      // if(piece==NULL) piece = board->getSpot(endX,startY)->getPiece();
                       if(piece == NULL) return std::pair<bool,Move*>(false,NULL); 
                       piece->setKilled(); 
                       m->setCaptering(true); 
                       board->killPiece(piece);
                       board->getSpot(startX,endY)->setPiece(NULL); 
                       board->getSpot(startX,endY)->setOccupied(false); 
                   } 
                }
            }
            // case where there is a capetering 
            if(end->isOccupied()){
               piece = end->getPiece(); 
               piece->setKilled();
               m->setCaptering(true); 
               board->killPiece(piece); 
            }
            end->setPiece(start->getPiece());
            end->setOccupied(true);
            if(end->getPiece()->getType() == 'K') {
                ((King*)end->getPiece())->setMoved(); 
            }
            if(end->getPiece()->getType() == 'R') {
                ((Rook*)end->getPiece())->setMoved(); 
            }

            start->setPiece(NULL); 
            start->setOccupied(false);
             
            return std::pair<bool,Move*>(true,m); 
        }
    } 
return std::pair<bool,Move*>(false,NULL);; 
}