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

std::vector<Move> generateLegalMoves(Position &position){
    std::vector<Move> legalMoves;
    auto pseudoMoves = generateAllMoves(position);
    Color side = position.sideToMove;

    for(auto move: pseudoMoves){
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