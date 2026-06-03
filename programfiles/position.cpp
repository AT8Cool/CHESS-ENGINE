/*
Store pieces
Store side to move
Apply move
Undo move

*/

#include "position.h"




Square convertSquare(std::string square){
    char file = square[0];
    char rank = square[1];

    int row = 8 - (rank - '0');
    int col = file - 'a' + 1;
    
    return {row,col};

}




