#ifndef UCIHELPER_H
#define UCIHELPER_H

#include <string>
#include "move.h"
#include "position.h"


void loadStartPosition(Position& position);
bool loadFen(Position& position, const std::string& fen);
std::string moveToUci(const Move& move);
bool parseUciMove(Position& position, const std::string& uciMove, Move& move);

#endif // UCIHELPER_H
