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


Square convertSquare(std::string square);


#endif