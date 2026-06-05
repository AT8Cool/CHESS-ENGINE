/* 
Legal?
Illegal?

For examples:
Pinned bishop?
King in check?
Castling through attack?

*/
#include "validatemove.h"

// std::vector<Move> generateAllMoves(Position &position)
// {
//     if(position.sideToMove == White)
//     {
//         return generateAllWhiteMoves(position);
//     }

//     return generateAllBlackMoves(position);
// }


Square Location(Position &position, char piece){
    Square Coordinates;
    for(int row = 0; row <8; row++){
        for(int col = 0; col <=8; col++){
            if(position.board[row][col] == piece){
              Coordinates.row = row;  
              Coordinates.col = col; 
              return Coordinates; 
            }
        }
    }
    return {-1,-1};
};




Square kingSquareFinder(Position &position, Color sideToMove){
    
    if(sideToMove == White){
   
        return Location(position,'K');
    }

    return Location(position,'k');


}





bool isKingInCheck(Position& position, Color side){

Square kingSquare = kingSquareFinder(position,side);
std::vector<Move> moves;

if(side == White){
    moves  =  generateAllBlackMoves(position);
}else{
    moves = generateAllWhiteMoves(position);
}

for(auto move:moves){
    if(move.toRow == kingSquare.row && 
        move.toCol == kingSquare.col){
        return true;
    } 
}

return false;
};

bool isCastleMove(const Move& move){

    return(move.fromRow == 7 && 
            move.fromCol == 5 && (move.toCol== 7 || move.toCol== 3))||
    
            (move.fromRow == 0 &&
            move.fromCol == 5 && (move.toCol == 7 || move.toCol == 3));
}


std::vector<Move> generateLegalMoves(Position &position){
    std::vector<Move> legalMoves;
    auto pseudoMoves = generateAllMoves(position);
    Color side = position.sideToMove;

    for(auto move: pseudoMoves){
        if(isCastleMove(move)){
            if(isKingInCheck(position,side)){
                continue;
            }
//Through Check White KingSide
            if(move.fromRow == 7 && 
                move.fromCol == 5 &&
                move.toCol == 7){
                    Position temp = position;

                    temp.board[7][5] = '.';
                    temp.board[7][6] = 'K';
                    if(isKingInCheck(temp,White)){
                        continue;
                    }
                }
//Through Check White QueenSide
            if(move.fromRow == 7 && 
                move.fromCol == 5 &&
                move.toCol == 3){
                    Position temp = position;

                    temp.board[7][5] = '.';
                    temp.board[7][4] = 'K';
                    if(isKingInCheck(temp,White)){
                        continue;
                    }
                }    
        


        //Through Check Black KingSide

        if(move.fromRow == 0 && 
                move.fromCol == 5 &&
                move.toCol == 7){
                    Position temp = position;

                    temp.board[0][5] = '.';
                    temp.board[0][6] = 'k';
                    if(isKingInCheck(temp,Black)){
                        continue;
                    }
                }

        

        //Through Check Black QueenSide

        if(move.fromRow == 0 && 
                move.fromCol == 5 &&
                move.toCol == 3){
                    Position temp = position;

                    temp.board[0][5] = '.';
                    temp.board[0][4] = 'k';
                    if(isKingInCheck(temp,Black)){
                        continue;
                    }
                }
        }

            
        makeMove(position,move);

        if(!isKingInCheck(position, side)){
            legalMoves.push_back(move);
        }
        undoMove(position,move);

        
    }

    return legalMoves;

}



bool isCheckmate(Position &position){
    return isKingInCheck(position, position.sideToMove)
    &&generateLegalMoves(position).empty();
}

bool isStalemate(Position &position, Color side){
    return !isKingInCheck(position, position.sideToMove)
    &&generateLegalMoves(position).empty();
}

