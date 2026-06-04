// for Legal move generation and futher testing

#include <iostream>
#include "board.h"
#include "position.h"
#include "genmoves.h"
#include "makemove.h"
#include "validatemove.h"
#include "evaluate.h"
#include "search.h"

int main()
{
    Position position;

    position.sideToMove = Black;

    char board[9][9] =
    {
        {'8','.','.','.','.','.','.','.','.'},
        {'7','.','.','.','.','.','.','.','.'},
        {'6','.','.','.','.','k','.','.','.'},
        {'5','.','.','.','.','.','.','.','.'},
        {'4','.','.','.','.','.','.','.','.'},
        {'3','.','.','.','p','.','.','.','.'},
        {'2','.','.','.','.','R','.','.','.'},
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

    std::cout << "\n Whiteking location:\n";

    Square king =
        kingSquareFinder(position,White);

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

    std::cout<<evaluate(position)<<"\n";

Move bestMove = bestMoveFinder(position, 4);

std::cout
    << bestMove.fromRow << ","
    << bestMove.fromCol
    << " -> "
    << bestMove.toRow << ","
    << bestMove.toCol
    << "\n";




    return 0;
}