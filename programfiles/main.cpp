#include <iostream>
#include "board.h"
#include "position.h"
#include "genmoves.h"

void printMoves(std::vector<Square> moves)
{
    for(auto move : moves)
    {
        std::cout << move.row
                  << " "
                  << move.col
                  << '\n';
    }
}

int main(){

   char board[9][9] =
{
    {'8','.','.','.','.','.','.','.','.'},
    {'7','.','.','.','.','.','.','.','.'},
    {'6','.','.','.','.','.','.','.','.'},
    {'5','.','.','.','.','.','.','.','.'},
    {'4','.','.','.','.','B','.','.','.'},
    {'3','.','.','.','.','.','.','.','.'},
    {'2','.','.','.','.','.','.','.','.'},
    {'1','.','.','.','.','.','.','.','.'},
    {' ','a','b','c','d','e','f','g','h'},
};

Square pawn = convertSquare("e2");
// auto moves = generateWhitePawnMoves(board,pawn);

auto moves =
    generateWhiteRookMoves(
        board,
        convertSquare("e4")
    );

printMoves(moves);

std::cout << moves.size() << '\n';


}