// for Legal move generation and futher testing

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
        {'4','.','R','.','.','.','.','.','.'},
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

    std::cout << "\nWhite king location:\n";

    Square king =
        kingSquareFinder(position, White);

    std::cout
        << king.row
        << " "
        << king.col
        << "\n";

    std::cout << "\nKing in check?\n";

    std::cout
        << isKingInCheck(position, White)
        << "\n";

    auto pseudoMoves =
        generateAllMoves(position);

    auto legalMoves =
        generateLegalMoves(position);

    std::cout
        << "\nPseudo Move Count: "
        << pseudoMoves.size()
        << "\n";

    std::cout
        << "Legal Move Count: "
        << legalMoves.size()
        << "\n";

    std::cout << "\nLegal Moves:\n";

    for(auto move : legalMoves)
    {
        std::cout
            << move.fromRow << ","
            << move.fromCol
            << " -> "
            << move.toRow << ","
            << move.toCol
            << "\n";
    }

    return 0;
}