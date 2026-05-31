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
    {'8','r','n','b','q','k','b','n','r'},
    {'7','p','p','p','p','p','p','p','p'},
    {'6','.','.','.','.','.','.','.','.'},
    {'5','.','.','.','.','.','.','.','.'},
    {'4','.','.','.','.','.','.','.','.'},
    {'3','.','.','.','.','.','.','.','.'},
    {'2','P','P','P','P','P','P','P','P'},
    {'1','R','N','B','Q','K','B','N','R'},
    {' ','a','b','c','d','e','f','g','h'},
};

Square pawn = convertSquare("e2");
// auto moves = generateWhitePawnMoves(board,pawn);

auto moves = generateWhiteKnightMoves(board, convertSquare("g1"));

printMoves(moves);


}