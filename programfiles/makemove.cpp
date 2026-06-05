#include "makemove.h"


void makeMove(Position &position, Move move){
        char piece = position.board[move.fromRow][move.fromCol];
            position.board[move.fromRow][move.fromCol] = '.';
                if(move.promotionPiece != '.')
                {
                    position.board[move.toRow][move.toCol] =
                        move.promotionPiece;
                }
                else
                {
                    position.board[move.toRow][move.toCol] = piece;
                }


}

void switchSideToMove(Position & position){
    if(position.sideToMove == White){

        position.sideToMove = Black;
    }
    else{
        position.sideToMove = White;
    }
}

void undoMove(Position &position, Move move)
{
    char piece = position.board[move.toRow][move.toCol];

    position.board[move.toRow][move.toCol] =
        move.capturedPiece;

    if(move.promotionPiece != '.')
    {
       if(isupper(move.promotionPiece))
{
    position.board[move.fromRow][move.fromCol] = 'P';
}
else
{
    position.board[move.fromRow][move.fromCol] = 'p';
}
    }
    else
    {
        position.board[move.fromRow][move.fromCol] = piece;
    }
}

std::vector<Move> generateAllMoves(Position &position)
{
    if(position.sideToMove == White)
    {
        return generateAllWhiteMoves(position);
    }

    return generateAllBlackMoves(position);
}


std::vector<Move> generateAllWhiteMoves(Position &position){
    std::vector<Move> allMoves;
    for(int row = 0; row <8; row++){
        for(int col = 1; col <=8; col++){
            char piece = position.board[row][col]; 
            Square Position = {row,col};
            
            if(piece != '.'){ 
                    // if it it a white piece then only execute
                    if(isupper(piece)){

                    if( piece == 'P'){
                        auto pawnMoves = generateWhitePawnMoves(position.board,Position);
                        
                      for(auto destination : pawnMoves){
                        Move Plays = {Position.row,
                            Position.col,
                            destination.row,
                            destination.col, 
                            position.board[destination.row][destination.col]};
                            //PROMOTION
                            if(destination.row == 0)
                            {
                                        Move queenMove = Plays;
                                        queenMove.promotionPiece = 'Q';
                                        allMoves.push_back(queenMove);

                                        Move rookMove = Plays;
                                        rookMove.promotionPiece = 'R';
                                        allMoves.push_back(rookMove);

                                        Move bishopMove = Plays;
                                        bishopMove.promotionPiece = 'B';
                                        allMoves.push_back(bishopMove);

                                        Move knightMove = Plays;
                                        knightMove.promotionPiece = 'N';
                                        allMoves.push_back(knightMove);
                                    }
                                    else
                                    {
                                        allMoves.push_back(Plays);
                                    }
                      }
                     
                    }

                    else if( piece == 'R'){
                        auto rookMoves = generateWhiteRookMoves(position.board,Position);
                        
                      for(auto destination : rookMoves){
                          Move Plays = {Position.row,Position.col,destination.row,destination.col, position.board[destination.row][destination.col]};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'N'){
                        auto knightMoves = generateWhiteKnightMoves(position.board,Position);
                        
                      for(auto destination : knightMoves){
                          Move Plays = {Position.row,Position.col,destination.row,destination.col, position.board[destination.row][destination.col]};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'B'){
                        auto bishopMoves = generateWhiteBishopMoves(position.board,Position);
                        
                      for(auto destination : bishopMoves){
                          Move Plays = {Position.row,Position.col,destination.row,destination.col, position.board[destination.row][destination.col]};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'Q'){
                        auto queenMoves = generateWhiteQueenMoves(position.board,Position);
                        
                      for(auto destination : queenMoves){
                          Move Plays = {Position.row,Position.col,destination.row,destination.col, position.board[destination.row][destination.col]};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'K'){
                        auto kingMoves = generateWhiteKingMoves(position.board,Position);
                        
                      for(auto destination : kingMoves){
                          Move Plays = {Position.row,Position.col,destination.row,destination.col, position.board[destination.row][destination.col]};
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
std::vector<Move> generateAllBlackMoves(Position &position){
    std::vector<Move> allMoves;
    for(int row = 0; row <8; row++){
        for(int col = 1; col <=8; col++){
            char piece = position.board[row][col]; 
            Square Position = {row,col};
            
            if(piece != '.'){ 
                    // if it it a black piece then only execute
                    if(islower(piece)){

                    if( piece == 'p'){
                        auto pawnMoves = generateBlackPawnMoves(position.board,Position);
                        
                      for(auto destination : pawnMoves){
                          Move Plays = {Position.row,
                            Position.col,
                            destination.row,
                            destination.col, 
                            position.board[destination.row][destination.col]};

                            if(destination.row == 7)
                            {
                                        Move queenMove = Plays;
                                        queenMove.promotionPiece = 'q';
                                        allMoves.push_back(queenMove);

                                        Move rookMove = Plays;
                                        rookMove.promotionPiece = 'r';
                                        allMoves.push_back(rookMove);

                                        Move bishopMove = Plays;
                                        bishopMove.promotionPiece = 'b';
                                        allMoves.push_back(bishopMove);

                                        Move knightMove = Plays;
                                        knightMove.promotionPiece = 'n';
                                        allMoves.push_back(knightMove);
                                    }
                                    else
                                    {
                                        allMoves.push_back(Plays);
                                    }

    
                      }
                     
                    }

                    else if( piece == 'r'){
                        auto rookMoves = generateBlackRookMoves(position.board,Position);
                        
                      for(auto destination : rookMoves){
                          Move Plays = {Position.row,Position.col,destination.row,destination.col, position.board[destination.row][destination.col]};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'n'){
                        auto knightMoves = generateBlackKnightMoves(position.board,Position);
                        
                      for(auto destination : knightMoves){
                          Move Plays = {Position.row,Position.col,destination.row,destination.col, position.board[destination.row][destination.col]};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'b'){
                        auto bishopMoves = generateBlackBishopMoves(position.board,Position);
                        
                      for(auto destination : bishopMoves){
                          Move Plays = {Position.row,Position.col,destination.row,destination.col, position.board[destination.row][destination.col]};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'q'){
                        auto queenMoves = generateBlackQueenMoves(position.board,Position);
                        
                      for(auto destination : queenMoves){
                          Move Plays = {Position.row,Position.col,destination.row,destination.col, position.board[destination.row][destination.col]};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'k'){
                        auto kingMoves = generateBlackKingMoves(position.board,Position);
                        
                      for(auto destination : kingMoves){
                          Move Plays = {Position.row,Position.col,destination.row,destination.col, position.board[destination.row][destination.col]};
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    
                        
                }
            }
        }
    }

    
    return allMoves;
}




