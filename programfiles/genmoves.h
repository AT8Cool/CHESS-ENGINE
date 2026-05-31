//genmoves.h

#ifndef GENMOVES_H
#define GENMOVES_H


#include<vector>
#include "position.h"

std::vector<Square> generatePawnMoves(
    char (&board)[9][9],
    Square position
);


#endif