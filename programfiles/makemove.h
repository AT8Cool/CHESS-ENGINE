#ifndef MAKEMOVE_H
#define MAKEMOVE_H
#include <vector>
#include<iostream>
#include "genmoves.h"
#include "position.h"
struct Move
{
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;

    char capturedPiece;
};

void makeMove(Position &position, Move move);
void switchSideToMove(Position & position);
void undoMove(Position &position, Move move);
std::vector<Move> generateAllMoves(Position &position);
std::vector<Move> generateAllWhiteMoves(Position &position);
std::vector<Move> generateAllBlackMoves(Position &position);

#endif