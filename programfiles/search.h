#ifndef SEARCH_H
#define SEARCH_H

#include "genmoves.h"
#include "evaluate.h"
#include "validatemove.h"
#include "makemove.h"
#include "position.h"
Move bestMoveFinder(Position &position, int depth);
int minimax(Position &position, int depth,int alpha,int beta);
int moveScore(Move move);

extern int nodes;

#endif