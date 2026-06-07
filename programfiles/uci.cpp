#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include "makemove.h"
#include "position.h"
#include "search.h"
#include "ucihelper.h"
#include "validatemove.h"

namespace
{
constexpr int kDefaultDepth = 4;

std::vector<std::string> splitCommand(const std::string& command)
{
    std::istringstream stream(command);
    std::vector<std::string> tokens;
    std::string token;

    while(stream >> token)
    {
        tokens.push_back(token);
    }

    return tokens;
}

void applyMoves(Position& position,
                const std::vector<std::string>& tokens,
                std::size_t startIndex)
{
    for(std::size_t index = startIndex;
        index < tokens.size();
        ++index)
    {
        Move move{};

        if(!parseUciMove(position, tokens[index], move))
        {
            break;
        }

        makeMove(position, move);
        switchSideToMove(position);
    }
}

void loadPositionFromCommand(Position& position,
                             const std::string& command)
{
    std::vector<std::string> tokens =
        splitCommand(command);

    if(tokens.size() < 2)
    {
        return;
    }

    if(tokens[1] == "startpos")
    {
        loadStartPosition(position);
    }
    else if(tokens[1] == "fen")
    {
        std::size_t movesIndex = tokens.size();

        for(std::size_t index = 2;
            index < tokens.size();
            ++index)
        {
            if(tokens[index] == "moves")
            {
                movesIndex = index;
                break;
            }
        }

        std::string fen;
        const std::size_t fenEnd =
            std::min<std::size_t>(2 + 6, movesIndex);

        for(std::size_t index = 2;
            index < fenEnd;
            ++index)
        {
            if(!fen.empty())
            {
                fen += ' ';
            }

            fen += tokens[index];
        }

        if(!loadFen(position, fen))
        {
            loadStartPosition(position);
        }
    }
    else
    {
        return;
    }

    for(std::size_t index = 0;
        index < tokens.size();
        ++index)
    {
        if(tokens[index] == "moves")
        {
            applyMoves(position, tokens, index + 1);
            break;
        }
    }
}

int parseDepth(const std::string& command)
{
    std::istringstream stream(command);
    std::string token;

    while(stream >> token)
    {
        if(token == "depth")
        {
            int depth = kDefaultDepth;

            if(stream >> depth && depth > 0)
            {
                return depth;
            }
        }
    }

    return kDefaultDepth;
}
}

int main()
{
    Position position;
    loadStartPosition(position);

    std::string command;

    while(std::getline(std::cin, command))
    {
        if(command == "uci")
        {
            std::cout << "id name AtharvaEngine\n";
            std::cout << "id author Atharva\n";
            std::cout << "uciok\n";
            std::cout.flush();
        }

        else if(command == "isready")
        {
            std::cout << "readyok\n";
            std::cout.flush();
        }

        else if(command == "ucinewgame")
        {
            loadStartPosition(position);
        }

        else if(command.rfind("position", 0) == 0)
        {
            loadPositionFromCommand(position, command);
        }

        else if(command.rfind("go", 0) == 0)
        {
            std::vector<Move> legalMoves =
                generateLegalMoves(position);

            if(legalMoves.empty())
            {
                std::cout << "bestmove 0000\n";
                std::cout.flush();
                continue;
            }

            nodes = 0;
            int depth = parseDepth(command);
            Move bestMove =
                bestMoveFinder(position, depth);

            std::cout
                << "info depth "
                << depth
                << " nodes "
                << nodes
                << " pv "
                << moveToUci(bestMove)
                << "\n";
            std::cout
                << "bestmove "
                << moveToUci(bestMove)
                << "\n";
            std::cout.flush();
        }

        else if(command == "stop" ||
                command.rfind("setoption", 0) == 0 ||
                command.rfind("debug", 0) == 0 ||
                command == "ponderhit")
        {
            continue;
        }

        else if(command == "quit")
        {
            break;
        }
    }

    return 0;
}
