#include <iostream>
#include "board.h"
#include "position.h"
#include "genmoves.h"
#include "makemove.h"
#include "validatemove.h"
#include "perft.h"

int main()
{
    Position position;

    position.sideToMove = White;

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

    // Copy board into Position
    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {
            position.board[row][col] = board[row][col];
        }
    }

    // std::cout << "Before Move:\n";
    // printBoard(position.board);

    // Move move = {6,5,4,5}; // e2 -> e4

    // makeMove(position, move);
    // switchSideToMove(position);

    // std::cout << "\nAfter Move:\n";
    // printBoard(position.board);

    // std::vector<Move> allMoves;

    // allMoves = generateAllMoves(position);


    // std::cout << "\nMove Count: "
    //           << allMoves.size()
    //           << "\n";

    // std::cout<< position.sideToMove<< "\n";

    // Square King = kingSquareFinder(position, White);

    // std::cout<< King.row<< " "<< King.col << "\n";
    // std::cout << isKingInCheck(position, White);



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
std::cout << "Perft(4): "
          << perft(position,4)
          << "\n";

divide(position, 2);
divide(position, 3);
    

    return 0;
}