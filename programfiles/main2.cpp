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

    // printBoard(position.board);

    // std::cout << "\n Whiteking location:\n";

    // Square king =
    //     kingSquareFinder(position,White);

    // std::cout
    //     << king.row
    //     << " "
    //     << king.col
    //     << "\n";

    // std::cout << "\nKing in check?\n";

    // std::cout
    //     << isKingInCheck(position, White)
    //     << "\n";

    // auto pseudoMoves =
    //     generateAllMoves(position);

    // auto legalMoves =
    //     generateLegalMoves(position);

    // std::cout
    //     << "\nPseudo Move Count: "
    //     << pseudoMoves.size()
    //     << "\n";

    // std::cout
    //     << "Legal Move Count: "
    //     << legalMoves.size()
    //     << "\n";

//     std::cout << "\nLegal Moves:\n";

//     for(auto move : legalMoves)
//     {
//         std::cout
//             << move.fromRow << ","
//             << move.fromCol
//             << " -> "
//             << move.toRow << ","
//             << move.toCol
//             << "\n";
//     }

//     std::cout<<evaluate(position)<<"\n";

// nodes = 0;
// Move bestMove = bestMoveFinder(position, 4);


// std::cout
//     << bestMove.fromRow << ","
//     << bestMove.fromCol
//     << " -> "
//     << bestMove.toRow << ","
//     << bestMove.toCol
//     << "\n";


// for(auto move : legalMoves)
// {
//     std::cout
//         << move.fromRow << ","
//         << move.fromCol << " -> "
//         << move.toRow << ","
//         << move.toCol
//         << " promotion="
//         << move.promotionPiece
//         << "\n";
// }

// std::cout
//     << "Nodes searched: "
//     << nodes
//     << "\n";


// Move testMove = legalMoves[0];
// Move testMove = {7,5,7,7,'.'};

// makeMove(position, testMove);

// std::cout << "\nAfter makeMove:\n";
// printBoard(position.board);

// undoMove(position, testMove);

// std::cout << "\nAfter undoMove:\n";
// printBoard(position.board);

// std::cout
//     << bestMove.fromRow << ","
//     << bestMove.fromCol
//     << " -> "
//     << bestMove.toRow << ","
//     << bestMove.toCol
//     << " promotion="
//     << bestMove.promotionPiece
//     << "\n";

//     std::cout << position.whiteKingsideRookMoved;

printBoard(position.board);

// auto legalMoves = generateLegalMoves(position);

// Move testMove{};

// testMove.fromRow = 3;
// testMove.fromCol = 5;

// testMove.toRow = 2;
// testMove.toCol = 4;

// testMove.capturedPiece = 'p';

// testMove.isEnPassant = true;

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

// std::cout << "\nCastling moves found:\n";

// for(auto move : legalMoves)
// {
//     if((move.fromRow == 7 && move.fromCol == 5 &&
//        (move.toCol == 7 || move.toCol == 3)))
//     {
//         std::cout
//             << move.fromRow << ","
//             << move.fromCol
//             << " -> "
//             << move.toRow << ","
//             << move.toCol
//             << "\n";
//     }
// }

// std::cout << "\nBefore move:\n";
// std::cout
//     << "whiteKingMoved="
//     << position.whiteKingMoved
//     << "\n";

// std::cout
//     << "whiteKingsideRookMoved="
//     << position.whiteKingsideRookMoved
//     << "\n";

//     Move testMove =  {6,5,4,5,'.', '.'};
// // if(!legalMoves.empty())
// // {
// //     testMove = legalMoves[0];
// // }else{
// //      std::cout << "No legal moves!\n";
// //     return 0;
// // }

// makeMove(position,testMove);
// std::cout
//     << "EP square: "
//     << position.enPassantRow
//     << ","
//     << position.enPassantCol
//     << "\n";

// printBoard(position.board);

// std::cout << "\nAfter makeMove:\n";
// printBoard(position.board);

// std::cout
//     << "whiteKingMoved="
//     << position.whiteKingMoved
//     << "\n";

// std::cout
//     << "whiteKingsideRookMoved="
//     << position.whiteKingsideRookMoved
//     << "\n";

// undoMove(position,testMove);

// std::cout << "\nAfter undoMove:\n";
// printBoard(position.board);

// std::cout
//     << "whiteKingMoved="
//     << position.whiteKingMoved
//     << "\n";

// std::cout
//     << "whiteKingsideRookMoved="
//     << position.whiteKingsideRookMoved
//     << "\n";
// std::cout
//     << "testMove: "
//     << testMove.fromRow << ","
//     << testMove.fromCol
//     << " -> "
//     << testMove.toRow << ","
//     << testMove.toCol
//     << "\n";
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