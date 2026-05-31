//genmoves.h

#ifndef GENMOVES_H
#define GENMOVES_H


#include<vector>
#include "position.h"
std::vector<Square> generateWhitePawnMoves(char (&board)[9][9],Square position);
std::vector<Square> generateWhiteKnightMoves(char (&board)[9][9],Square position);
std::vector<Square> generateWhiteBishopMoves(char (&board)[9][9],Square position);
std::vector<Square> generateWhiteRookMoves(char (&board)[9][9],Square position);
std::vector<Square> generateWhiteQueenMoves(char (&board)[9][9],Square position);
std::vector<Square> generateMovesWhiteKing(char (&board)[9][9], Square position);


#endif