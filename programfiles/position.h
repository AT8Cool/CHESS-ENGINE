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
};


Square convertSquare(std::string square);


#endif