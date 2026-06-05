// This file is only related to the displaying of the board and the pieces based on the required positions on the board.

// Render board
// Print board
// Convert board state to human-readable form

#include<iostream>
#include "position.h"


using namespace std;


void printBoard(char (&board)[9][9]){
for(int i = 0; i< 9; i++){
    for(int j = 0; j< 9; j++){
        cout << board[i][j] << " ";
    }
    cout << endl;
}
}

void makeMove( char(&board)[9][9], Square from, Square to){
    
    char piece = board[from.row][from.col];

    board[from.row][from.col] = '.';
    board[to.row][to.col] = piece;

}




    









