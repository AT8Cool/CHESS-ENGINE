#ifndef POSITION_H
#define POSITION_H

#include<string>

struct Square{
    int row; 
    int col;

};

enum Color{
    White,
    Black
};

struct Position{
    char board[9][9];
    Color sideToMove;

    bool whiteKingMoved = false;
    bool blackKingMoved = false;

    bool whiteKingsideRookMoved = false;
    bool whiteQueensideRookMoved = false;

    bool blackKingsideRookMoved = false;
    bool blackQueensideRookMoved = false;

    int enPassantRow = -1;
    int enPassantRow = -1;
};


Square convertSquare(std::string square);


#endif