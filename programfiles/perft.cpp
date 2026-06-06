#include "perft.h"
#include "position.h"
#include "validatemove.h"
#include "makemove.h"
#include <iostream>


long long perft(Position& position, int depth)
{
    if(depth == 0)
    {
        return 1;
    }

    long long nodes = 0;

    auto legalMoves =
        generateLegalMoves(position);

    for(auto move : legalMoves)
    {
        makeMove(position, move);

        switchSideToMove(position);

        nodes += perft(
            position,
            depth - 1
        );

        switchSideToMove(position);

        undoMove(position, move);
    }

    

    return nodes;
}

void divide(Position& position, int depth)
{
    auto legalMoves =
        generateLegalMoves(position);

    long long total = 0;

    for(auto move : legalMoves)
    {
        makeMove(position, move);

        switchSideToMove(position);

        long long nodes =
            perft(position, depth - 1);

        switchSideToMove(position);

        undoMove(position, move);

        std::cout
            << move.fromRow << ","
            << move.fromCol
            << " -> "
            << move.toRow << ","
            << move.toCol
            << " : "
            << nodes
            << "\n";

        total += nodes;
    }

    std::cout
        << "\nTotal: "
        << total
        << "\n";
}