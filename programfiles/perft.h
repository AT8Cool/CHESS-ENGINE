#ifndef PERFT_H
#define PERFT_H

#include "position.h"

long long perft(Position& position, int depth);
void divide(Position& position, int depth);


#endif