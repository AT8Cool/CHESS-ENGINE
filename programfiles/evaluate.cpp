/*

Material count
Pawn   = 100
Knight = 300
Bishop = 300
Rook   = 500
Queen  = 900

*/ 

#include "evaluate.h"

int evaluate(Position &position){
    int score =0;
    for(int row = 0; row<8; row++){
        for(int col =1; col <=8; col++){
            char piece = position.board[row][col];

            switch (piece)
            {
            case 'P':score += 100;break;
            case 'N':score += 300;break;
            case 'B':score += 300;break;
            case 'R':score += 500;break;
            case 'Q':score += 900;break;
            //FOR TESTING PURPOSE ONLY LATER REMOVE THE BELOW CASE
            case 'K': score +=20000; break;
            
            case 'p':score -= 100;break;
            case 'n':score -= 300;break;
            case 'b':score -= 300;break;
            case 'r':score -= 500;break;
            case 'q':score -= 900;break;
            //FOR TESTING PURPOSE ONLY LATER REMOVE THE BELOW CASE
            case 'k': score -=20000; break;
        
            }
        }
    }
    return score;
}

