#include <iostream>
#include "board.h"
#include "position.h"
#include "genmoves.h"
#include "makemove.h"
#include "validatemove.h"

int main()
{
    Position position;

    position.sideToMove = White;

   char board[9][9] =
{
    {'8','.','.','.','.','r','.','.','.'},
    {'7','.','.','.','.','.','.','.','.'},
    {'6','.','.','.','.','.','.','.','.'},
    {'5','.','.','.','.','.','.','.','.'},
    {'4','.','.','.','.','.','.','.','.'},
    {'3','.','.','.','.','.','.','.','.'},
    {'2','.','.','.','.','.','.','.','.'},
    {'1','.','.','.','.','K','.','.','.'},
    {' ','a','b','c','d','e','f','g','h'},
};

    // Copy board into Position
    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {
            position.board[row][col] = board[row][col];
        }
    }

    std::cout << "Before Move:\n";
    printBoard(position.board);

    Move move = {6,5,4,5}; // e2 -> e4

    makeMove(position, move);
    switchSideToMove(position);

    std::cout << "\nAfter Move:\n";
    printBoard(position.board);

    std::vector<Move> allMoves;

    allMoves = generateAllMoves(position);


    std::cout << "\nMove Count: "
              << allMoves.size()
              << "\n";

    std::cout<< position.sideToMove<< "\n";

    Square King = kingSquareFinder(position, White);

    std::cout<< King.row<< " "<< King.col << "\n";
    std::cout << isKingInCheck(position, White);

    return 0;
}