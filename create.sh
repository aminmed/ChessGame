#!/bin/bash


g++  ./src/Clock.cpp \
./src/Piece.cpp  \
./src/Bishop.cpp \
 ./src/King.cpp \
./src/Queen.cpp \ 
./src/Knight.cpp  \
./src/Pawn.cpp  \
./src/Rook.cpp  \
./src/Player.cpp \
./src/MinMaxPlayer.cpp  \
./src/Spot.cpp \
./src/Board.cpp  \
./src/Move.cpp \
./src/PGNio.cpp \
./src/Game.cpp \
./src/main.cpp \
-static
mv ./src/a.out ./chess