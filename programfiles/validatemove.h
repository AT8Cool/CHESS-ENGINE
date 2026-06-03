#ifndef VALIDATEMOVE_H
#define VALIDATEMOVE_H


#include "board.h"
#include "genmoves.h"
#include "position.h"
#include "makemove.h"

Square kingSquareFinder(Position &position, Color sideToMove);
Square Location(Position &position, char piece);
bool isKingInCheck(Position& position, Color side);
std::vector<Move> generateLegalMoves(Position &position);


#endif