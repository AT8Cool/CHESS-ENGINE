#include <iostream>
#include "board.h"
#include "position.h"
#include "search.h"

int main()
{
    Position position;

    position.sideToMove = White;

  char board[9][9] =
{
    {'8','.','.','.','r','k','.','.','.'},
    {'7','.','.','.','.','.','.','.','.'},
    {'6','.','.','.','.','.','.','.','.'},
    {'5','.','.','.','q','.','.','.','.'},
    {'4','.','.','.','Q','.','.','.','.'},
    {'3','.','.','.','.','.','.','.','.'},
    {'2','.','.','.','.','.','.','.','.'},
    {'1','.','.','.','.','K','.','.','.'},
    {' ','a','b','c','d','e','f','g','h'},
};

    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {
            position.board[row][col] = board[row][col];
        }
    }

    printBoard(position.board);

    std::cout
        << "\nEvaluation: "
        << evaluate(position)
        << "\n";

    auto moves =
        generateLegalMoves(position);

    std::cout
        << "\nLegal Moves:\n";

    for(auto move : moves)
    {
        std::cout
            << move.fromRow << ","
            << move.fromCol
            << " -> "
            << move.toRow << ","
            << move.toCol
            << " capture="
            << move.capturedPiece
            << "\n";
    }

    std::cout
        << "\nBest Move Depth 1:\n";

    Move best =
        bestMoveFinder(position,1);

    std::cout
        << best.fromRow << ","
        << best.fromCol
        << " -> "
        << best.toRow << ","
        << best.toCol
        << "\n";

    return 0;
}