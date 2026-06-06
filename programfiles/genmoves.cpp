/*
Position
↓
Generate candidate moves
This file doesnt care about the legality of the moves, or if the generated moves 
are the best or not. i.e It doesnt matter your king ends up in  check or vulenerbale.

*/
#include "genmoves.h"

std::vector<Move> generateEnPassantMoves(Position &position){
    std::vector<Move> epMoves;
        if(position.enPassantRow == -1){
            return epMoves;
        }
        //WHITE ENPASSANT

        if(position.sideToMove == White)
                {
                    int row = position.enPassantRow;
                    int col = position.enPassantCol;
                    

                    if(row + 1 < 8 &&
                    col - 1 >= 1 &&
                    position.board[row + 1][col - 1] == 'P')
                    {  
                        Move move{};
                        move.isEnPassant = true;
                        move.fromRow = row + 1;
                        move.fromCol = col - 1;

                        move.toRow = row;
                        move.toCol = col;

                        move.capturedPiece = 'p';
                        move.promotionPiece = '.';

                        epMoves.push_back(move);
                    }

                    if(row + 1 < 8 &&
                    col + 1 <= 8 &&
                    position.board[row + 1][col + 1] == 'P')
                    {
                        Move move{};

                        move.isEnPassant = true;
                        move.fromRow = row + 1;
                        move.fromCol = col + 1;

                        move.toRow = row;
                        move.toCol = col;

                        move.capturedPiece = 'p';
                        move.promotionPiece = '.';

                        epMoves.push_back(move);
                    }
                }
      
            //BLACK ENPASSANT
            if(position.sideToMove == Black)
            {
                int row = position.enPassantRow;
                int col = position.enPassantCol;

                if(row - 1 >= 0 &&
                col - 1 >= 1 &&
                position.board[row - 1][col - 1] == 'p')
                {
                    Move move{};

                    move.isEnPassant = true;
                    move.fromRow = row - 1;
                    move.fromCol = col - 1;

                    move.toRow = row;
                    move.toCol = col;

                    move.capturedPiece = 'P';
                    move.promotionPiece = '.';

                    epMoves.push_back(move);
                }

                if(row - 1 >= 0 &&
                col + 1 <= 8 &&
                position.board[row - 1][col + 1] == 'p')
                {
                    Move move{};

                    move.isEnPassant = true;
                    move.fromRow = row - 1;
                    move.fromCol = col + 1;

                    move.toRow = row;
                    move.toCol = col;

                    move.capturedPiece = 'P';
                    move.promotionPiece = '.';

                    epMoves.push_back(move);
                }
            }

            return epMoves;

}

//==============================================White pieces==============================================
//BELOW THIS ARE THE WHITE PIECE MOVES
//WHITE PAWN MOVES
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

//WHITE KNIGHT MOVES
std::vector<Square> generateWhiteKnightMoves(char (&board)[9][9],Square position){
    std::vector<Square> moves;
    
    int row = position.row;
    int col = position.col;

    int knightMoves[8][2] ={

        {2,1},
        {2,-1},
        {-2, 1},
        {-2,-1},

        {1,2},
        {1,-2},
        {-1,2},
        {-1,-2}

    };

    for(int i = 0; i< 8; i++){
        int newRow = row + knightMoves[i][0];
        int newCol = col + knightMoves[i][1];

        if(newRow >= 0 && newRow <=7 and newCol >=1 and newCol <= 8 && !isupper(board[newRow][newCol])){
            
            moves.push_back({newRow,newCol});

        }
    }
    return moves;

}
//WHITE BISHOP MOVES
std::vector<Square> generateWhiteBishopMoves(char (&board)[9][9], Square position){
    std::vector<Square> moves;

    int BishopMoves[4][2] = {
        {1,1},
        {1,-1},
        {-1,1},
        {-1,-1}
    };

    for(int i = 0; i <4; i++){
        int row = position.row;
        int col = position.col;

        for(int steps = 1; steps<8; steps++){

            int newRow = row + BishopMoves[i][0] * steps;
            int newCol = col + BishopMoves[i][1] * steps;

        
            
            if(newRow <= 7 && newRow >=0 && newCol >= 1 && newCol <= 8 ){
            
                char target = board[newRow][newCol];

                if(target == '.'){
                     moves.push_back({newRow,newCol});
                }
                else if(islower(target)){
                     moves.push_back({newRow,newCol});
                     break;
                }
                
                else if(isupper(target)){
                    break;
                }
                else{
                    break;
                }
            }

        }

    }
return moves;

}

//WHITE ROOK MOVES
std::vector<Square> generateWhiteRookMoves(char (&board)[9][9], Square position){
    std::vector<Square> moves;
    
    int RookMoves[4][2] = {{0,1},
                           {1,0},
                           {-1,0},
                           {0,-1}
                            };
    int row = position.row;
    int col = position.col;

    for(int i = 0; i< 4; i++){
        for(int steps = 1; steps < 8; steps++){
            int newRow = row + RookMoves[i][0] * steps;
            int newCol = col + RookMoves[i][1] * steps;

            if(newRow <= 7 && newRow >= 0 && newCol >=1 && newCol <= 8){
                char target = board[newRow][newCol];

                if(target == '.'){
                     moves.push_back({newRow,newCol});
                }
                else if(islower(target)){
                     moves.push_back({newRow,newCol});
                     break;
                }
                
                else if(isupper(target)){
                    break;
                }
                else{
                    break;
                }
            }

        }

    }
return moves;
};

//WHITE QUEEN MOVES
std::vector<Square> generateWhiteQueenMoves(char (&board)[9][9], Square position){
    std::vector<Square> moves;

    int row = position.row;
    int col = position.col;

    int QueenMoves[8][2] = {
                          {0,1},
                           {1,0},
                           {-1,0},
                           {0,-1},
                           {1,1},
                            {1,-1},
                            {-1,1},
                            {-1,-1}
    };


    for(int i = 0; i <8; i++){
        for(int steps = 1; steps< 8;steps++){

            int newRow = row + QueenMoves[i][0] * steps;
            int newCol = col + QueenMoves[i][1] * steps;

            if(newRow >= 0 && newRow <=7 && newCol >=1 && newCol <=8 ){
                char target = board[newRow][newCol];

                if(target == '.'){
                     moves.push_back({newRow,newCol});
                }
                else if(islower(target)){
                     moves.push_back({newRow,newCol});
                     break;
                }
                
                else if(isupper(target)){
                    break;
                }
                else{
                    break;
                }

            }

        }
    }
return moves;
};

//WHITE KING MOVES
std::vector<Square> generateWhiteKingMoves(char (&board)[9][9], Square position){
    std::vector<Square> moves;

    int row = position.row;
    int col = position.col;

    int KingMoves[8][2] = {
                          {0,1},
                           {1,0},
                           {-1,0},
                           {0,-1},
                           {1,1},
                            {1,-1},
                            {-1,1},
                            {-1,-1}
    }; 

    for(int i = 0; i< 8; i++){
        int newRow = row + KingMoves[i][0];
        int newCol = col + KingMoves[i][1];

        if(newRow >=0 && newRow <= 7 && newCol >=1 && newCol <=8){
            
            char target = board[newRow][newCol];
            if(target == '.'){
                moves.push_back({newRow,newCol});

            }else if(islower(target)){
                     moves.push_back({newRow,newCol});
                     
            }else if(isupper(target)){
                    continue;
            }

        }
    }

    return moves;

}



//==============================================Black pieces==============================================

//BELOW THIS ARE THE BLACK PIECE MOVES
//BLACK PAWN MOVES
std::vector<Square> generateBlackPawnMoves(char (&board)[9][9],Square position){
    std::vector<Square> moves;

     int forward = position.row +1;
     int doubleForward = position.row + 2;

    //Movements    
    if(board[forward][position.col] == '.'){
    
    moves.push_back({forward,position.col});

        if(board[doubleForward][position.col] == '.' && position.row == 1){
             moves.push_back({doubleForward, position.col});
        }
   }
    // Capturing moves

    // Check left diagonal
    if(position.col < 8){
            if(isupper(board[forward][position.col+1])){
            moves.push_back({forward,position.col+1});
        }
    }
   

    //Check right diagonal
    if(position.col > 1){
            if(isupper(board[forward][position.col-1])){
            moves.push_back({forward,position.col-1});
        }
    }
    
    return moves;
}

// BLACK KNIGHT MOVES
std::vector<Square> generateBlackKnightMoves(char (&board)[9][9],Square position){
    std::vector<Square> moves;
    
    int row = position.row;
    int col = position.col;

    int knightMoves[8][2] ={

        {2,1},
        {2,-1},
        {-2, 1},
        {-2,-1},

        {1,2},
        {1,-2},
        {-1,2},
        {-1,-2}

    };

    for(int i = 0; i< 8; i++){
        int newRow = row + knightMoves[i][0];
        int newCol = col + knightMoves[i][1];

        if(newRow >= 0 && newRow <=7 and newCol >=1 and newCol <= 8 && !islower(board[newRow][newCol])){
            
            moves.push_back({newRow,newCol});

        }
    }
    return moves;

}

//BLACK BISHOP MOVES

std::vector<Square> generateBlackBishopMoves(char (&board)[9][9], Square position){
    std::vector<Square> moves;

    int BishopMoves[4][2] = {
        {1,1},
        {1,-1},
        {-1,1},
        {-1,-1}
    };

    for(int i = 0; i <4; i++){
        int row = position.row;
        int col = position.col;

        for(int steps = 1; steps<8; steps++){

            int newRow = row + BishopMoves[i][0] * steps;
            int newCol = col + BishopMoves[i][1] * steps;

        
            
            if(newRow <= 7 && newRow >=0 && newCol >= 1 && newCol <= 8 ){
            
                char target = board[newRow][newCol];

                if(target == '.'){
                     moves.push_back({newRow,newCol});
                }
                else if(isupper(target)){
                     moves.push_back({newRow,newCol});
                     break;
                }
                
                else if(islower(target)){
                    break;
                }
                else{
                    break;
                }
            }

        }

    }
return moves;

}

//BLACK ROOK MOVES
std::vector<Square> generateBlackRookMoves(char (&board)[9][9], Square position){
    std::vector<Square> moves;
    
    int RookMoves[4][2] = {{0,1},
                           {1,0},
                           {-1,0},
                           {0,-1}
                            };
    int row = position.row;
    int col = position.col;

    for(int i = 0; i< 4; i++){
        for(int steps = 1; steps < 8; steps++){
            int newRow = row + RookMoves[i][0] * steps;
            int newCol = col + RookMoves[i][1] * steps;

            if(newRow <= 7 && newRow >= 0 && newCol >=1 && newCol <= 8){
                char target = board[newRow][newCol];

                if(target == '.'){
                     moves.push_back({newRow,newCol});
                }
                else if(isupper(target)){
                     moves.push_back({newRow,newCol});
                     break;
                }
                
                else if(islower(target)){
                    break;
                }
                else{
                    break;
                }
            }

        }

    }
return moves;
};

//BLACK QUEEN MOVES
std::vector<Square> generateBlackQueenMoves(char (&board)[9][9], Square position){
    std::vector<Square> moves;

    int row = position.row;
    int col = position.col;

    int QueenMoves[8][2] = {
                          {0,1},
                           {1,0},
                           {-1,0},
                           {0,-1},
                           {1,1},
                            {1,-1},
                            {-1,1},
                            {-1,-1}
    };


    for(int i = 0; i <8; i++){
        for(int steps = 1; steps< 8;steps++){

            int newRow = row + QueenMoves[i][0] * steps;
            int newCol = col + QueenMoves[i][1] * steps;

            if(newRow >= 0 && newRow <=7 && newCol >=1 && newCol <=8 ){
                char target = board[newRow][newCol];

                if(target == '.'){
                     moves.push_back({newRow,newCol});
                }
                else if(isupper(target)){
                     moves.push_back({newRow,newCol});
                     break;
                }
                
                else if(islower(target)){
                    break;
                }
                else{
                    break;
                }

            }

        }
    }
return moves;
};

//BLACK KING MOVES

std::vector<Square> generateBlackKingMoves(char (&board)[9][9], Square position){
    std::vector<Square> moves;

    int row = position.row;
    int col = position.col;

    int KingMoves[8][2] = {
                          {0,1},
                           {1,0},
                           {-1,0},
                           {0,-1},
                           {1,1},
                            {1,-1},
                            {-1,1},
                            {-1,-1}
    }; 

    for(int i = 0; i< 8; i++){
        int newRow = row + KingMoves[i][0];
        int newCol = col + KingMoves[i][1];

        if(newRow >=0 && newRow <= 7 && newCol >=1 && newCol <=8){
            
            char target = board[newRow][newCol];
            if(target == '.'){
                moves.push_back({newRow,newCol});

            }else if(isupper(target)){
                     moves.push_back({newRow,newCol});
                     
            }
    }
    }
    return moves;

}



