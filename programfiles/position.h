#ifndef POSITION_H
#define POSITION_H

#include<string>

struct Square{
    int row; 
    int col;

};

Square convertSquare(std::string square);


#endif