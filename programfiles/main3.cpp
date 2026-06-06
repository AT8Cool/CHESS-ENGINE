#include <iostream>

#include "board.h"
#include "position.h"
#include "move.h"
#include "genmoves.h"
#include "makemove.h"
#include "validatemove.h"

int main()
{
    Position position;

    position.sideToMove = White;

    char board[9][9] =
    {
        {'8','.','.','.','.','k','.','.','.'},
        {'7','.','.','.','.','.','.','.','.'},
        {'6','.','.','.','.','.','.','.','.'},
        {'5','.','.','.','p','P','.','.','.'},
        {'4','.','.','.','.','.','.','.','.'},
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

    // Simulate black just played d7-d5
    // position.enPassantRow = 2;
    // position.enPassantCol = 4;

    // std::cout << "Initial Position:\n";
    // printBoard(position.board);

    // auto legalMoves =
    //     generateLegalMoves(position);

    // std::cout << "\nGenerated Moves:\n";

    // for(auto move : legalMoves)
    // {
    //     std::cout
    //         << move.fromRow << ","
    //         << move.fromCol
    //         << " -> "
    //         << move.toRow << ","
    //         << move.toCol
    //         << " EP="
    //         << move.isEnPassant
    //         << "\n";
    // }

    // Move epMove{};

    // bool found = false;

    // for(auto move : legalMoves)
    // {
    //     if(move.isEnPassant)
    //     {
    //         epMove = move;
    //         found = true;
    //         break;
    //     }
    // }

    // if(!found)
    // {
    //     std::cout
    //         << "\nNO EN PASSANT MOVE FOUND\n";

    //     return 0;
    // }

    // std::cout
    //     << "\nTesting move:\n"
    //     << epMove.fromRow << ","
    //     << epMove.fromCol
    //     << " -> "
    //     << epMove.toRow << ","
    //     << epMove.toCol
    //     << "\n";

    // makeMove(position, epMove);

    // std::cout
    //     << "\nAfter makeMove:\n";

    // printBoard(position.board);

    // undoMove(position, epMove);

    // std::cout
    //     << "\nAfter undoMove:\n";

    // printBoard(position.board);

    #include "perft.h"

std::cout << "Perft(0): "
          << perft(position,0)
          << "\n";

std::cout << "Perft(1): "
          << perft(position,1)
          << "\n";

std::cout << "Perft(2): "
          << perft(position,2)
          << "\n";

std::cout << "Perft(3): "
          << perft(position,3)
          << "\n";
    return 0;
}