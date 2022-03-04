#include "Piece.h"
#include "Board.h"
Piece::Piece(bool isBlack){
    this->black = isBlack; 
    if(!isBlack) {
        this->printedValue = ' '; 
    }
}
Piece::Piece(){}
Piece::~Piece() {}
bool Piece::isBlack(){
    return this->black; 
}
std::string  Piece::getPrintedValue(){
    return this->printedValue; 
}
void Piece::setPrintedValue(std::string value) {
    this->printedValue = value; 
}
void Piece::setType(char t) {this->type = t;}
char Piece::getType(){return this->type;}
void Piece::setKilled(){
    this->killed = true; 
}