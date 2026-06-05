/*

Material count
Pawn   = 100
Knight = 300
Bishop = 300
Rook   = 500
Queen  = 900

*/ 

#include "evaluate.h"
int pieceValue(char piece){
switch (piece)
            {
            case 'P': return 100;
            case 'N': return 300;
            case 'B': return 300;
            case 'R': return 500;
            case 'Q': return 900;
            case 'K': return 20000;

            case 'p': return -100;
            case 'n': return -300;
            case 'b': return -300;
            case 'r': return -500;
            case 'q': return -900;
            case 'k': return -20000;

            default: return 0;
        
            }



}
//Piece-Square Table 
int knightTable[8][8] =
{
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}
};

int pieceSquareBonus(char piece, int row, int col){
    if(piece == 'N'){
        return knightTable[row][col];
    }

    if(piece == 'n'){
        return -knightTable[7-row][col];
    }
    return 0;
}

int evaluate(Position &position){
    int score =0;
    for(int row = 0; row<8; row++){
        for(int col =1; col <=8; col++){
            char piece = position.board[row][col];
            score += pieceValue(piece);

            score += pieceSquareBonus(piece,row,col-1);
        }
    }
    return score;
}

