/*

Here happens the key responsiblites
MiniMax Alpha-beta pruning
Move ordering 
 
this file should call
genmoves
validatemove
evaluate



 */


#include "search.h"

int minimax(Position &position, int depth){
    if(depth ==0){
        return evaluate(position);
    }
    auto moves = generateLegalMoves(position);

    if(moves.empty()){
        std::cout<< "Terminal Position \n";
        if(isKingInCheck(position,position.sideToMove)){
            std::cout<< "CHECKMATE\n";
            if(position.sideToMove == White){
                return -100000;
            }else{
                return 100000;
            }
        }
        std::cout<< "STALEMATE\n";
        return 0;
    }


if(position.sideToMove == White){
       int bestScore = INT_MIN;

        for(auto move:moves){

             makeMove(position,move);
             switchSideToMove(position);

             int score = minimax(position, depth-1);

             switchSideToMove(position);
             undoMove(position,move);

             if(score > bestScore){
                bestScore = score;
             }
             
        }
        return bestScore;


    }
       int bestScore = INT_MAX;
        
       for(auto move:moves)
       {

             makeMove(position,move);
             switchSideToMove(position);

             int score = minimax(position, depth-1);

             switchSideToMove(position);
             undoMove(position,move);

             if(score < bestScore)
             {
                bestScore = score;
             }
        }
        return bestScore;

    }
    


Move bestMoveFinder(Position &position){
      auto moves = generateLegalMoves(position);
      if(moves.empty()){
        return{-1,-1,-1,-1,'.'};
      } 
        Move bestMove = moves[0];   
        if(position.sideToMove == White){
            int bestScore = INT_MIN;
                for(auto move: moves){
                    makeMove(position,move);
                    switchSideToMove(position);

                int score = minimax(position,2);
                switchSideToMove(position); 
                undoMove(position, move);

                if(score > bestScore){
                    bestScore = score;
                    bestMove = move;
                }
                }
            
                return bestMove;
                }

                int bestScore = INT_MAX;

                for(auto move: moves){
                    makeMove(position,move);
                    switchSideToMove(position);

                int score = minimax(position,2);
                switchSideToMove(position); 
                undoMove(position, move);

                         std::cout
        << move.fromRow << ","
        << move.fromCol
        << " -> "
        << move.toRow << ","
        << move.toCol
        << " score="
        << score
        << "\n";

                if(score < bestScore){
                    bestScore = score;
                    bestMove = move;

           
                }
                }
                
            return bestMove;
               

}











