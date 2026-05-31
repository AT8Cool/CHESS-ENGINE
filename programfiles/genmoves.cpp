/*
Position
↓
Generate candidate moves
This file doesnt care about the legality of the moves, or if the generated moves 
are the best or not. i.e It doesnt matter your king ends up in  check or vulenerbale.

*/
#include "genmoves.h"


std::vector<Square> generateWhitePawnMoves(char (&board)[9][9],Square position){
    std::vector<Square> moves;

     int forward = position.row -1;
     int doubleForward = position.row - 2;

    //Movements    
    if(board[forward][position.col] == '.'){
    
    moves.push_back({forward,position.col});

        if(board[doubleForward][position.col] == '.' && position.row == 6){
             moves.push_back({doubleForward, position.col});
        }
   }
    // Capturing moves

    // Check left diagonal
    if(position.col > 1){
            if(islower(board[forward][position.col-1])){
            moves.push_back({forward,position.col-1});
        }
    }
   

    //Check right diagonal
    if(position.col < 8){
            if(islower(board[forward][position.col+1])){
            moves.push_back({forward,position.col+1});
        }
    }
    


   


    return moves;
}


