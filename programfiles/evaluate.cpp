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

int evaluate(Position &position){
    int score =0;
    for(int row = 0; row<8; row++){
        for(int col =1; col <=8; col++){
            score += pieceValue(position.board[row][col]);

            
        }
    }
    return score;
}

