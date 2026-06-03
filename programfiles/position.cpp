/*
Store pieces
Store side to move
Apply move
Undo move

*/


// enum PieceType{
//     Pawn,
//     Rook,
//     Knight,
//     Bishop,
//     Queen,
//     King
// };


// PieceType piece = Pawn;
// PieceType piece = Rook;
// PieceType piece = Knight;
// PieceType piece = Bishop;
// PieceType piece = King;
// PieceType piece = Queen;

// enum Color{
//     White,
//     Black
// };

// Color sideToMove = White;
// Color sideToMove = Black;


#include "position.h"




Square convertSquare(std::string square){
    char file = square[0];
    char rank = square[1];

    int row = 8 - (rank - '0');
    int col = file - 'a' + 1;
    
    return {row,col};

}




