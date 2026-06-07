#include "ucihelper.h"
#include <cctype>
#include <sstream>
#include <vector>
#include "makemove.h"
#include "validatemove.h"

namespace
{
constexpr const char* kStartFen =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

void initialiseBoard(Position& position)
{
    for(int row = 0; row < 8; ++row)
    {
        position.board[row][0] =
            static_cast<char>('8' - row);

        for(int col = 1; col <= 8; ++col)
        {
            position.board[row][col] = '.';
        }
    }

    position.board[8][0] = ' ';

    for(int col = 1; col <= 8; ++col)
    {
        position.board[8][col] =
            static_cast<char>('a' + col - 1);
    }
}

void resetState(Position& position)
{
    position.sideToMove = White;

    position.whiteKingMoved = true;
    position.blackKingMoved = true;

    position.whiteKingsideRookMoved = true;
    position.whiteQueensideRookMoved = true;

    position.blackKingsideRookMoved = true;
    position.blackQueensideRookMoved = true;

    position.enPassantRow = -1;
    position.enPassantCol = -1;
}

std::vector<std::string> split(const std::string& input)
{
    std::istringstream stream(input);
    std::vector<std::string> tokens;
    std::string token;

    while(stream >> token)
    {
        tokens.push_back(token);
    }

    return tokens;
}

std::string normaliseMoveText(std::string moveText)
{
    for(char& ch : moveText)
    {
        ch = static_cast<char>(
            std::tolower(
                static_cast<unsigned char>(ch)
            )
        );
    }

    return moveText;
}
}

void loadStartPosition(Position& position)
{
    loadFen(position, kStartFen);
}

bool loadFen(Position& position, const std::string& fen)
{
    std::vector<std::string> fields = split(fen);

    if(fields.size() < 4)
    {
        return false;
    }

    initialiseBoard(position);
    resetState(position);

    int row = 0;
    int col = 1;

    for(char token : fields[0])
    {
        if(token == '/')
        {
            ++row;
            col = 1;
            continue;
        }

        if(std::isdigit(static_cast<unsigned char>(token)))
        {
            int emptySquares = token - '0';

            for(int index = 0; index < emptySquares; ++index)
            {
                if(row > 7 || col > 8)
                {
                    return false;
                }

                position.board[row][col] = '.';
                ++col;
            }

            continue;
        }

        if(row > 7 || col > 8)
        {
            return false;
        }

        position.board[row][col] = token;
        ++col;
    }

    position.sideToMove =
        fields[1] == "b" ? Black : White;

    const std::string& castling = fields[2];
    const bool whiteCanCastleKingside =
        castling.find('K') != std::string::npos;
    const bool whiteCanCastleQueenside =
        castling.find('Q') != std::string::npos;
    const bool blackCanCastleKingside =
        castling.find('k') != std::string::npos;
    const bool blackCanCastleQueenside =
        castling.find('q') != std::string::npos;

    position.whiteKingMoved =
        !(whiteCanCastleKingside || whiteCanCastleQueenside);
    position.blackKingMoved =
        !(blackCanCastleKingside || blackCanCastleQueenside);

    position.whiteKingsideRookMoved =
        !whiteCanCastleKingside;
    position.whiteQueensideRookMoved =
        !whiteCanCastleQueenside;

    position.blackKingsideRookMoved =
        !blackCanCastleKingside;
    position.blackQueensideRookMoved =
        !blackCanCastleQueenside;

    if(fields[3] != "-")
    {
        Square enPassantSquare =
            convertSquare(fields[3]);

        position.enPassantRow =
            enPassantSquare.row;
        position.enPassantCol =
            enPassantSquare.col;
    }

    return true;
}

std::string moveToUci(const Move& move)
{
    if(move.fromRow < 0 || move.fromCol < 1 ||
       move.toRow < 0 || move.toCol < 1)
    {
        return "0000";
    }

    std::string uciMove;

    uciMove +=
        static_cast<char>('a' + move.fromCol - 1);
    uciMove +=
        static_cast<char>('8' - move.fromRow);
    uciMove +=
        static_cast<char>('a' + move.toCol - 1);
    uciMove +=
        static_cast<char>('8' - move.toRow);

    if(move.promotionPiece != '.')
    {
        uciMove += static_cast<char>(
            std::tolower(
                static_cast<unsigned char>(
                    move.promotionPiece
                )
            )
        );
    }

    return uciMove;
}

bool parseUciMove(Position& position, const std::string& uciMove, Move& move)
{
    const std::string targetMove =
        normaliseMoveText(uciMove);

    std::vector<Move> legalMoves =
        generateLegalMoves(position);

    for(const Move& legalMove : legalMoves)
    {
        if(moveToUci(legalMove) == targetMove)
        {
            move = legalMove;
            return true;
        }
    }

    return false;
}
