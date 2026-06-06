#ifndef MOVE_H
#define MOVE_H
struct Move
{
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;

    char capturedPiece;
    char promotionPiece;


    bool oldWhiteKingMoved;
    bool oldBlackKingMoved;

    bool oldWhiteKingsideRookMoved;
    bool oldWhiteQueensideRookMoved;

    bool oldBlackKingsideRookMoved;
    bool oldBlackQueensideRookMoved;

    bool isEnPassant= false;
    int oldEnPassantRow;
    int oldEnPassantCol;

};


#endif