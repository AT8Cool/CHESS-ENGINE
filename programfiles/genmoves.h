//genmoves.h

#ifndef GENMOVES_H
#define GENMOVES_H


#include<vector>
#include "position.h"
#include "move.h"


//White Moves
std::vector<Square> generateWhitePawnMoves(char (&board)[9][9],Square position);
std::vector<Square> generateWhiteKnightMoves(char (&board)[9][9],Square position);
std::vector<Square> generateWhiteBishopMoves(char (&board)[9][9],Square position);
std::vector<Square> generateWhiteRookMoves(char (&board)[9][9],Square position);
std::vector<Square> generateWhiteQueenMoves(char (&board)[9][9],Square position);
std::vector<Square> generateWhiteKingMoves(char (&board)[9][9], Square position);

//Black Moves
std::vector<Square> generateBlackPawnMoves(char (&board)[9][9],Square position);
std::vector<Square> generateBlackKnightMoves(char (&board)[9][9],Square position);
std::vector<Square> generateBlackBishopMoves(char (&board)[9][9],Square position);
std::vector<Square> generateBlackRookMoves(char (&board)[9][9],Square position);
std::vector<Square> generateBlackQueenMoves(char (&board)[9][9],Square position);
std::vector<Square> generateBlackKingMoves(char (&board)[9][9], Square position);

std::vector<Move> generateEnPassantMoves(Position & position);

#endif