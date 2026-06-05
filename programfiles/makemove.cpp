#include "makemove.h"


void makeMove(Position &position, Move &move){

        char piece = position.board[move.fromRow][move.fromCol];
        
            //Save castling righst for undo 
                move.oldWhiteKingMoved = position.whiteKingMoved;
                move.oldBlackKingMoved = position.blackKingMoved;

                move.oldWhiteKingsideRookMoved = position.whiteKingsideRookMoved;
                move.oldWhiteQueensideRookMoved = position.whiteQueensideRookMoved;

                move.oldBlackKingsideRookMoved = position.blackKingsideRookMoved;
                move.oldBlackQueensideRookMoved = position.blackQueensideRookMoved;


            //Update castling rights
            if(piece == 'K'){
                position.whiteKingMoved = true;
            }

            if(piece == 'k'){
                position.blackKingMoved = true;
            }
            if(piece == 'R'){
                if(move.fromRow == 7 && move.fromCol==8){
                    position.whiteKingsideRookMoved= true;
                }

                if(move.fromRow == 7 && move.fromCol==1){
                    position.whiteQueensideRookMoved= true;
                }

            }
            if(piece == 'r'){
                if(move.fromRow == 0 && move.fromCol==8){
                    position.blackKingsideRookMoved= true;
                }

                if(move.fromRow == 0 && move.fromCol==1){
                    position.blackQueensideRookMoved= true;
                }

            }

           
            //Castling rights
            //White Kingside Castling
            if(piece == 'K' &&
            move.fromRow == 7 &&
            move.fromCol == 5 &&
            move.toRow == 7 &&
            move.toCol == 7)
            {
                position.board[7][8] = '.';
                position.board[7][6] = 'R';
            }
            //White Queenside Castling
            if(piece == 'K' &&
                move.fromRow == 7 &&
                move.fromCol == 5 &&
                move.toRow == 7 &&
                move.toCol == 3)
                {
                    position.board[7][1] = '.';
                    position.board[7][4] = 'R';
                }
            //Black Kingside Castling
            if(piece == 'k' &&
            move.fromRow == 0 && move.fromCol == 5 &&
            move.toRow == 0 && move.toCol == 7)
            {
                position.board[0][8] = '.';
                position.board[0][6] = 'r';
            }
            //Black Queenside Castling
            if(piece == 'k' &&
                move.fromRow == 0 &&
                move.fromCol == 5 &&
                move.toRow == 0 &&
                move.toCol == 3)
                {
                    position.board[0][1] = '.';
                    position.board[0][4] = 'r';
                }
                //normal move

                 position.board[move.fromRow][move.fromCol] = '.';
                 //Promotion
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

void undoMove(Position &position, Move &move)
{
    char piece =
        position.board[move.toRow][move.toCol];
     

    // Restore castling rights
    position.whiteKingMoved =
        move.oldWhiteKingMoved;

    position.blackKingMoved =
        move.oldBlackKingMoved;

    position.whiteKingsideRookMoved =
        move.oldWhiteKingsideRookMoved;

    position.whiteQueensideRookMoved =
        move.oldWhiteQueensideRookMoved;

    position.blackKingsideRookMoved =
        move.oldBlackKingsideRookMoved;

    position.blackQueensideRookMoved =
        move.oldBlackQueensideRookMoved;

    // Undo castling

    // White kingside
    if(move.fromRow == 7 &&
       move.fromCol == 5 &&
       move.toRow == 7 &&
       move.toCol == 7)
    {
        position.board[7][6] = '.';
        position.board[7][8] = 'R';
    }

    // White queenside
    if(move.fromRow == 7 &&
       move.fromCol == 5 &&
       move.toRow == 7 &&
       move.toCol == 3)
    {
        position.board[7][4] = '.';
        position.board[7][1] = 'R';
    }

    // Black kingside
    if(move.fromRow == 0 &&
       move.fromCol == 5 &&
       move.toRow == 0 &&
       move.toCol == 7)
    {
        position.board[0][6] = '.';
        position.board[0][8] = 'r';
    }

    // Black queenside
    if(move.fromRow == 0 &&
       move.fromCol == 5 &&
       move.toRow == 0 &&
       move.toCol == 3)
    {
        position.board[0][4] = '.';
        position.board[0][1] = 'r';
    }

    // Remove moved piece
    position.board[move.toRow][move.toCol] =
        move.capturedPiece;

    // Undo promotion
    if(move.promotionPiece != '.')
    {
        if(isupper(move.promotionPiece))
        {
            position.board[move.fromRow][move.fromCol] =
                'P';
        }
        else
        {
            position.board[move.fromRow][move.fromCol] =
                'p';
        }
    }
    else
    {
        position.board[move.fromRow][move.fromCol] =
            piece;
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
                        Move Plays{};

                            Plays.fromRow = Position.row;
                            Plays.fromCol = Position.col;
                            Plays.toRow = destination.row;
                            Plays.toCol = destination.col;
                            Plays.capturedPiece =
                                position.board[destination.row][destination.col];
                            Plays.promotionPiece = '.';

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
                          Move Plays{};
                          Plays.fromRow = Position.row;
                          Plays.fromCol = Position.col;
                          Plays.toRow = destination.row;
                          Plays.toCol = destination.col;
                          Plays.capturedPiece = position.board[destination.row][destination.col];
                          Plays.promotionPiece = '.';
                            
                         
                         
                         
                            allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'N'){
                        auto knightMoves = generateWhiteKnightMoves(position.board,Position);
                        
                      for(auto destination : knightMoves){
                          Move Plays{};
                          Plays.fromRow = Position.row;
                          Plays.fromCol = Position.col;
                          Plays.toRow = destination.row;
                          Plays.toCol = destination.col;
                          Plays.capturedPiece = position.board[destination.row][destination.col];
                          Plays.promotionPiece = '.';
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'B'){
                        auto bishopMoves = generateWhiteBishopMoves(position.board,Position);
                        
                      for(auto destination : bishopMoves){
                          Move Plays{};
                          Plays.fromRow = Position.row;
                          Plays.fromCol = Position.col;
                          Plays.toRow = destination.row;
                          Plays.toCol = destination.col;
                          Plays.capturedPiece = position.board[destination.row][destination.col];
                          Plays.promotionPiece = '.';
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'Q'){
                        auto queenMoves = generateWhiteQueenMoves(position.board,Position);
                        
                      for(auto destination : queenMoves){
                          Move Plays{};
                          Plays.fromRow = Position.row;
                          Plays.fromCol = Position.col;
                          Plays.toRow = destination.row;
                          Plays.toCol = destination.col;
                          Plays.capturedPiece = position.board[destination.row][destination.col];
                          Plays.promotionPiece = '.';
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'K'){
                        auto kingMoves = generateWhiteKingMoves(position.board,Position);
                        
                      for(auto destination : kingMoves){
                          Move Plays{};
                          Plays.fromRow = Position.row;
                          Plays.fromCol = Position.col;
                          Plays.toRow = destination.row;
                          Plays.toCol = destination.col;
                          Plays.capturedPiece = position.board[destination.row][destination.col];
                          Plays.promotionPiece = '.';


                            allMoves.push_back(Plays);
                      }
                      //whiteKingsideRookMoved
                       if(!position.whiteKingMoved && !position.whiteKingsideRookMoved){
                                if(position.board[7][6] == '.' && position.board[7][7]=='.' && position.board[7][8] == 'R'){
                                    Move castle{};
                                        castle.fromRow = 7;
                                        castle.fromCol = 5;
                                        castle.toRow = 7;
                                        castle.toCol = 7;
                                        castle.capturedPiece = '.';
                                        castle.promotionPiece = '.';

                                        allMoves.push_back(castle);
                                }
                            }
                        //whiteQueenSideRookMoved
                        if(!position.whiteKingMoved && !position.whiteQueensideRookMoved){
                                if(position.board[7][2] == '.' && position.board[7][3]=='.' && position.board[7][4]=='.' && position.board[7][1] == 'R'){
                                    Move castle{};
                                        castle.fromRow = 7;
                                        castle.fromCol = 5;
                                        castle.toRow = 7;
                                        castle.toCol = 3;
                                        castle.capturedPiece = '.';
                                        castle.promotionPiece = '.';

                                        allMoves.push_back(castle);
                                }
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
                          Move Plays{};

                            Plays.fromRow = Position.row;
                            Plays.fromCol = Position.col;
                            Plays.toRow = destination.row;
                            Plays.toCol = destination.col;
                            Plays.capturedPiece =
                                position.board[destination.row][destination.col];
                            Plays.promotionPiece = '.';

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
                          Move Plays{};
                          Plays.fromRow = Position.row;
                          Plays.fromCol = Position.col;
                          Plays.toRow = destination.row;
                          Plays.toCol = destination.col;
                          Plays.capturedPiece = position.board[destination.row][destination.col];
                          Plays.promotionPiece = '.';
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'n'){
                        auto knightMoves = generateBlackKnightMoves(position.board,Position);
                        
                      for(auto destination : knightMoves){
                          Move Plays{};
                          Plays.fromRow = Position.row;
                          Plays.fromCol = Position.col;
                          Plays.toRow = destination.row;
                          Plays.toCol = destination.col;
                          Plays.capturedPiece = position.board[destination.row][destination.col];
                          Plays.promotionPiece = '.';
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'b'){
                        auto bishopMoves = generateBlackBishopMoves(position.board,Position);
                        
                      for(auto destination : bishopMoves){
                          Move Plays{};
                          Plays.fromRow = Position.row;
                          Plays.fromCol = Position.col;
                          Plays.toRow = destination.row;
                          Plays.toCol = destination.col;
                          Plays.capturedPiece = position.board[destination.row][destination.col];
                          Plays.promotionPiece = '.';
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'q'){
                        auto queenMoves = generateBlackQueenMoves(position.board,Position);
                        
                      for(auto destination : queenMoves){
                          Move Plays{};
                          Plays.fromRow = Position.row;
                          Plays.fromCol = Position.col;
                          Plays.toRow = destination.row;
                          Plays.toCol = destination.col;
                          Plays.capturedPiece = position.board[destination.row][destination.col];
                          Plays.promotionPiece = '.';
                         allMoves.push_back(Plays);
                      }
                     
                    }
                    else if( piece == 'k'){
                        auto kingMoves = generateBlackKingMoves(position.board,Position);
                        
                      for(auto destination : kingMoves){
                          Move Plays{};
                          Plays.fromRow = Position.row;
                          Plays.fromCol = Position.col;
                          Plays.toRow = destination.row;
                          Plays.toCol = destination.col;
                          Plays.capturedPiece = position.board[destination.row][destination.col];
                          Plays.promotionPiece = '.';
                         
                         
                          allMoves.push_back(Plays);
                      }

                          //BlackKingsideRookMoved
                       if(!position.blackKingMoved && !position.blackKingsideRookMoved){
                                if(position.board[0][6] == '.' && position.board[0][7]=='.' && position.board[0][8] == 'r'){
                                    Move castle{};
                                        castle.fromRow = 0;
                                        castle.fromCol = 5;
                                        castle.toRow = 0;
                                        castle.toCol = 7;
                                        castle.capturedPiece = '.';
                                        castle.promotionPiece = '.';

                                        allMoves.push_back(castle);
                                }
                            }
                        //BlackQueenSideRookMoved
                        if(!position.blackKingMoved && !position.blackQueensideRookMoved){
                                if(position.board[0][2] == '.' && position.board[0][3]=='.' && position.board[0][4]=='.' && position.board[0][1] == 'r'){
                                    Move castle{};
                                        castle.fromRow = 0;
                                        castle.fromCol = 5;
                                        castle.toRow = 0;
                                        castle.toCol = 3;
                                        castle.capturedPiece = '.';
                                        castle.promotionPiece = '.';

                                        allMoves.push_back(castle);
                                }
                            }

                      }
                     
                    }
                    
                        
                }
            }
        }
    

    return allMoves;
}




