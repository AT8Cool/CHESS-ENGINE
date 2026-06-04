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
 int nodes = 0;
int minimax(Position &position, int depth,int alpha, int beta){
   
    nodes++;

    if(depth ==0){
        return evaluate(position);
    }
    auto moves = generateLegalMoves(position);

    if(moves.empty()){
        
        if(isKingInCheck(position,position.sideToMove)){
        
            if(position.sideToMove == White){
                return -100000;
            }else{
                return 100000;
            }
        }
       
        return 0;
    }

//WHITE NODE
if(position.sideToMove == White){
       int bestScore = INT_MIN;

        for(auto move:moves){

             makeMove(position,move);
             switchSideToMove(position);

             int score = minimax(position, depth-1,alpha,beta);

             switchSideToMove(position);
             undoMove(position,move);

             if(score > bestScore){
                bestScore = score;
             }
             if(score > alpha){
                alpha = score;
             }
             if(alpha >=beta){
                break;
             }
             
        }
        return bestScore;


    }
       int bestScore = INT_MAX;
        
       for(auto move:moves)
       {

             makeMove(position,move);
             switchSideToMove(position);

             int score = minimax(position, depth-1,alpha,beta);

             switchSideToMove(position);
             undoMove(position,move);

            if(score < bestScore){
                bestScore = score;
             }
             if(score < beta)
             {
                beta = score;
             }
             if(alpha >= beta){
                break;
             }
        }
        return bestScore;

    }

Move bestMoveFinder(Position &position, int depth){
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

                int score = minimax(position,depth-1, INT_MIN, INT_MAX);
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

                int score = minimax(position,depth-1,INT_MIN,INT_MAX);
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











