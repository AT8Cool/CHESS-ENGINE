#ifndef MAKEMOVE_H
#define MAKEMOVE_H
#include <vector>
#include<iostream>
#include "genmoves.h"
struct Move
{
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
};

void makeMove(char (&board)[9][9], Move move);
std::vector<Move> generateAllWhiteMoves(char (&board)[9][9]);
std::vector<Move> generateAllBlackMoves(char (&board)[9][9]);

#endif