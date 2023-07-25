/***********************************************************************
 * File			:	Board.cpp
 * Author		:	鐘詩靈 B11115010
 *					陳仕興 B11115011
 *					魏美芳 B11115014
 * Create Date	:	2023-05-08
 * Editor		:	鐘詩靈 B11115010
 *					陳仕興 B11115011
 *					魏美芳 B11115014
 * Update Date	:	2023-05-17
 * Description	:	This C++ program simulates chess game with Guardians of the Galaxy theme
*************************************************************************/

#include "Player.h"

#include "knight.h"
#include "rook.h"
#include "king.h"
#include "bishop.h"
#include "queen.h"
#include "pawn.h"

// Intent: Initialize a Player object with the given parameters.
// Pre: Copy the 'board' parameter to the player object 'board'.
// Post: The Player object is initialized with the specified parameters.
Player::Player(char(&board)[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->board[i][j] = board[i][j];
        }
    }
}

// Intent: Get the color of the player object.
// Pre: The 'piece' parameter represents the color of the given piece.
// Post: If the given 'piece' is on upper case return "WHITE", if it is on lower case return "BLACK".
QString Player::getColor(char piece)
{
    if (isupper(piece))
    {
        return "WHITE";
    }

    return "BLACK";
}

// Intent: Get the piece in the given position.
// Pre: The 'pos' parameter represents the position of a piece in the board.
// Post: Return the icon of the piece in the given position.
char Player::getPieceAt(Position pos)
{
    return this->board[pos.y][pos.x];
}

// Intent: Set a piece to a position.
// Pre: The 'pos' parameter represents the designated position, the 'piece' parameter represents the piece to move.
// Post: Set the piece at the given position.
void Player::setPieceAt(Position pos, char piece)
{
    this->board[pos.y][pos.x] = piece;
}

// Intent: Get the pieces of a player.
// Pre: The 'color' parameter represents which player's piece that need to be returned.
// Post: Return the pieces of a player.
QVector<Position> Player::getOwnPieces(QString color)
{
    QVector<Position> ownPieces;

    // If the player color is "WHITE" set isWhite to true, vice versa
    bool isWhite = color == "WHITE" ? true : false;

    // Iterates through the board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Position currPos(j, i);
            char piece = getPieceAt(currPos);

            // If there is no piece in the current board skip it
            if (piece == ' ')
            {
                continue;
            }

            // If the player is white and the piece icon is on upper case which indicates that it is a white piece,
            // Appends the position to the ownPieces vector
            if (isWhite && isupper(piece))
            {
                ownPieces.push_back(currPos);
            }
            // If the player is black and the piece icon is on lower case which indicates that it is a black piece,
            // Appends the position to the ownPieces vector
            else if (!isWhite && !isupper(piece))
            {
                ownPieces.push_back(currPos);
            }
        }
    }

    return ownPieces;   // Return ownPieces
}

// Intent: Get the pieces of a player.
// Pre: The 'color' parameter represents which player's piece that need to be returned.
// Post: Return the pieces of a player.
QVector<Position> Player::getEnemyPieces(QString color)
{
    QVector<Position> enemyPieces;
    bool isWhite = color == "WHITE" ? true : false;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Position currPos(j, i);
            char piece = this->board[i][j];

            if (piece == ' ') {
                continue;
            }

            if (isWhite && !isupper(piece)) {
                enemyPieces.push_back(currPos);
            }
            else if (!isWhite && isupper(piece)) {
                enemyPieces.push_back(currPos);
            }
        }
    }

    return enemyPieces;
}

// Intent: To check whether the king is on check or not.
// Pre: The 'color' parameter represents the player color,
//      the 'kingPos' parameter represents the position of the player's king,
//      the 'gBoard' represents the game board.
// Post: Return true if the king is on check, return false if not.
bool Player::isUnderAttack(QString color, Position kingPos, Board gBoard)
{
    QVector<Position> enemyPos = getEnemyPieces(color);

    bool isWhite = color == "WHITE" ? true : false;

    // Iterates through all the position of the enemy vector
    for (Position& ePos : enemyPos)
    {
        QVector<Position> possibleMoves;    // To store all the current piece possible moves
        char piece = getPieceAt(ePos);  // Copy the piece icon to 'piece'

        // If the player color is black copy all the possible moves of white pieces
        if(!isWhite)
        {
            // Appends all the enemy pieces' possible moves
            if (piece == 'P')
            {
                Pawn piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'K')
            {
                King piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'Q')
            {
                Queen piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'B')
            {
                Bishop piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'N')
            {
                Knight piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'R')
            {
                Rook piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
        }
        // If the player color is white copy all the possible moves of black pieces
        else
        {
            // Appends all the enemy pieces' possible moves
            if (piece == 'p')
            {
                Pawn piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'k')
            {
                King piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'q')
            {
                Queen piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'b')
            {
                Bishop piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'n')
            {
                Knight piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'r')
            {
                Rook piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
        }

        // Iterates all the possible moves
        for (Position& move : possibleMoves)
        {
            // If one of the possible moves is the same with the king position return true
            if (move == kingPos)
            {
                return true;
            }
        }
    }

    return false;   // If no possible moves that is the same with king's position, return false
}

// Intent: To check whether the king is on checkmate or not.
// Pre: The 'color' parameter represents the player color,
//      the 'kingPos' parameter represents the position of the player's king,
//      the 'gBoard' represents the game board.
// Post: Return true if the king is on check, return false if not.
bool Player::isCheckMate(QString color, Position kingPos, Board gBoard)
{
    bool isWhite = color == "WHITE" ? true : false;
    QString enemyColor = color == "WHITE" ? "BLACK" : "WHITE";

    // Check if the king is in check
    if (!isUnderAttack(color, kingPos, gBoard))
    {
        return false; // King is not in check, not checkmate
    }

    // Generate all possible moves for the player
    QVector<Position> playerPos = getOwnPieces(color);
    for (Position& ePos : playerPos)
    {
        QVector<Position> possibleMoves;    // To store all the current piece possible moves
        char piece = getPieceAt(ePos);  // Copy the piece icon to 'piece'

        // If the player color is white copy all the possible moves of white pieces
        if (isWhite)
        {
            // Appends all the enemy pieces' possible moves
            if (piece == 'P')
            {
                Pawn piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'K')
            {
                King piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'Q')
            {
                Queen piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'B')
            {
                Bishop piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'N')
            {
                Knight piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'R')
            {
                Rook piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
        }
        // If the player color is black copy all the possible moves of black pieces
        else
        {
            // Appends all the enemy pieces' possible moves
            if (piece == 'p')
            {
                Pawn piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'k')
            {
                King piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'q')
            {
                Queen piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'b')
            {
                Bishop piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'n')
            {
                Knight piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
            else if (piece == 'r')
            {
                Rook piece(isWhite, ePos);
                possibleMoves = piece.getSimulation(gBoard);
            }
        }

        // Simulate each move and check if the king is still in check
        for (const Position& move : possibleMoves)
        {
            Board tempBoard = gBoard; // Create a copy of the board
            char pieceAtMove = tempBoard.board[move.y][move.x]; // Store the piece at the move position

            // Simulate the move by updating the positions on the tempBoard
            tempBoard.setPieceAt(move, piece);
            tempBoard.setPieceAt(ePos, ' ');

            // Check if the opponent's king is still under attack in the simulated board
            if (!isUnderAttack(enemyColor, kingPos, tempBoard))
            {
                return false; // King is not in checkmate
            }

            // Restore the original piece at the move position
            tempBoard.setPieceAt(move, pieceAtMove);
        }
    }

    return true; // King is in checkmate
}

// Intent: To get the position of a king.
// Pre: The 'color' parameter represents the player color,
// Post: Return the position of a king with the same color.
Position Player::getKingPosition(QString color)
{
    bool isWhite = color == "WHITE" ? true : false;

    // Iterates the board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // If the king with the given color has been found, return the position
            if (isWhite && this->board[i][j] == 'K')
            {
                return Position(j, i);
            }
            else if (!isWhite && this->board[i][j] == 'k')
            {
                return Position(j, i);
            }
        }
    }

    return Position(-1, -1);    // If not found return -1, -1
};
