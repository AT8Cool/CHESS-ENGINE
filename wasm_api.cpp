#include <string>

#include "programfiles/position.h"
#include "programfiles/search.h"
#include "programfiles/ucihelper.h"

extern "C" const char* findBestMove(const char* fen, int depth)
{
    static std::string uciMove = "0000";

    Position position{};

    if(fen == nullptr || depth <= 0 || !loadFen(position, fen))
    {
        uciMove = "0000";
        return uciMove.c_str();
    }

    Move bestMove = bestMoveFinder(position, depth);
    uciMove = moveToUci(bestMove);

    return uciMove.c_str();
}
