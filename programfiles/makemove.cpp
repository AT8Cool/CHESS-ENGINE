#include "makemove.h"


void makeMove(char (&board)[9][9], Move move){
    char piece = board[move.fromRow][move.fromCol];

    board[move.fromRow][move.fromCol] = '.';
    board[move.toRow][move.toCol] = piece;
}

std::vector<Move> generateAllWhiteMoves(char (&board)[9][9]){
    std::vector<Move> allMoves;
    for(int row = 0; row <8; row++){
        for(int col = 1; col <=8; col++){
            char piece = board[row][col]; 
            Square Position = {row,col};
            
            if(piece != '.'){ 
                    // if it it a white piece then only execute
                    if(isupper(piece)){

                    if( piece == 'P'){
                        auto pawnMoves = generateWhitePawnMoves(board,Position);
                        
                      for(auto destination : pawnMoves){
                          Move Plays = {Position.row,Position.col,destination.row,destination.col};
                         allMoves.push_back(Plays);
                      }
                     
                    }

                    else if( piece == 'R'){
                        auto rookMoves = generateWhiteRookMoves(board,Position);
                        
                      for(auto destination : rookMoves){
                          Move Plays = {Position.row,Position.col, destination.row,destination.col};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'N'){
                        auto knightMoves = generateWhiteKnightMoves(board,Position);
                        
                      for(auto destination : knightMoves){
                          Move Plays = {Position.row,Position.col, destination.row,destination.col};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'B'){
                        auto bishopMoves = generateWhiteBishopMoves(board,Position);
                        
                      for(auto destination : bishopMoves){
                          Move Plays = {Position.row,Position.col, destination.row,destination.col};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'Q'){
                        auto queenMoves = generateWhiteQueenMoves(board,Position);
                        
                      for(auto destination : queenMoves){
                          Move Plays = {Position.row,Position.col, destination.row,destination.col};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'K'){
                        auto kingMoves = generateWhiteKingMoves(board,Position);
                        
                      for(auto destination : kingMoves){
                          Move Plays = {Position.row,Position.col, destination.row,destination.col};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    
                        
                }
            }
        }
    }
    


    return allMoves;
}


//Generation of all possible black moves
std::vector<Move> generateAllBlackMoves(char (&board)[9][9]){
    std::vector<Move> allMoves;
    for(int row = 0; row <8; row++){
        for(int col = 1; col <=8; col++){
            char piece = board[row][col]; 
            Square Position = {row,col};
            
            if(piece != '.'){ 
                    // if it it a black piece then only execute
                    if(islower(piece)){

                    if( piece == 'p'){
                        auto pawnMoves = generateBlackPawnMoves(board,Position);
                        
                      for(auto destination : pawnMoves){
                          Move Plays = {Position.row,Position.col,destination.row,destination.col};
                         allMoves.push_back(Plays);
                      }
                     
                    }

                    else if( piece == 'r'){
                        auto rookMoves = generateBlackRookMoves(board,Position);
                        
                      for(auto destination : rookMoves){
                          Move Plays = {Position.row,Position.col, destination.row,destination.col};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'n'){
                        auto knightMoves = generateBlackKnightMoves(board,Position);
                        
                      for(auto destination : knightMoves){
                          Move Plays = {Position.row,Position.col, destination.row,destination.col};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'b'){
                        auto bishopMoves = generateBlackBishopMoves(board,Position);
                        
                      for(auto destination : bishopMoves){
                          Move Plays = {Position.row,Position.col, destination.row,destination.col};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'q'){
                        auto queenMoves = generateBlackQueenMoves(board,Position);
                        
                      for(auto destination : queenMoves){
                          Move Plays = {Position.row,Position.col, destination.row,destination.col};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'k'){
                        auto kingMoves = generateBlackKingMoves(board,Position);
                        
                      for(auto destination : kingMoves){
                          Move Plays = {Position.row,Position.col, destination.row,destination.col};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    
                        
                }
            }
        }
    }




    return allMoves;
}





