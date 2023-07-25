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

#include "knight.h"
#include <cctype>
#include <QDebug>
#include <player.h>

Knight::Knight(bool isWhite, Position position)
{
    this->position = position;

    if (isWhite) {
        this->imgUrl = ":/images/images/gKnight.png";
        this->color = "WHITE";
    }
    else {
        this->imgUrl = ":/images/images/vKnight.png";
        this->color = "BLACK";
    }
}

//Intent = Retrieve all possible moves for the Knight on the given board.
//Pre = A valid Board object 'gBoard' is provided.
//Pos = A QVector containing all legal moves for the Knight is returned.
QVector<Position> Knight::getPossibleMove(Board gBoard) {
    QVector<Position> legalMoves;

    // Create a Player object to access the board state
    Player player(gBoard.board);

    // Define the possible moves in x and y directions
    int xDir[] = {-1, -1, 1, 1, -2, -2, 2, 2};
    int yDir[] = {-2, 2, -2, 2, -1, 1, -1, 1};

    // Check all possible moves
    for (int i = 0; i < 8; i++)
    {
        int newX = position.x + xDir[i];
        int newY = position.y + yDir[i];

        Position newPos(newX, newY);

        // Check if the new position is within the board boundaries
        if (newPos.isInRange())
        {
            char pieceAtNewPosition = player.board[newY][newX];
            QString pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

            if (pieceAtNewPosition == ' ' || pieceAtNewPositionColor != this->color)
            {
                // Create a temporary board to simulate the move
                Board tempBoard;

                // Copy the current board state to the temporary board
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        tempBoard.board[row][col] = player.board[row][col];
                    }
                }

                // Determine the piece representation and the current position
                char piece = this->color == "WHITE" ? 'N' : 'n';
                int oldX = this->position.x;
                int oldY = this->position.y;

                // Update the temporary board with the new position
                tempBoard.board[newY][newX] = piece;
                tempBoard.board[oldY][oldX] = ' ';

                // Get the position of the current player's king
                Position kingPos = player.getKingPosition(this->color);

                // Check if the player's king is under attack in the temporary board
                if (!player.isUnderAttack(this->color, kingPos, tempBoard))
                {
                    // Add the new position to the legal moves
                    legalMoves.push_back(newPos);
                }
            }
        }
    }

    return legalMoves;
}

//Intent = Move the Knight to the target position on the board.
//Pre = A valid Board object 'gBoard' is provided, and the target position is within the board boundaries.
//Pos = The Knight is moved to the target position on the board, and the last moved piece position is updated.
void Knight::move(Board& gBoard, Position targetPos) {
    // Determine the current piece representation
    char currentPiece = this->color == "WHITE" ? 'N' : 'n';

    // Set the target position and the current position with the current piece
    gBoard.setPieceAt(targetPos, currentPiece);
    gBoard.setPieceAt(this->position, ' ');
    gBoard.lastMovedPiecePosition = targetPos;
}

//Intent = Retrieve all possible moves for the Knight in a simulation.
//Pre = A valid Board object 'gBoard' is provided.
//Pos = A QVector containing all legal moves for the Knight in the simulation is returned.
QVector<Position> Knight::getSimulation(Board gBoard) {
    QVector<Position> legalMoves;
    Player player(gBoard.board);

    // Define the possible moves in x and y directions
    int xDir[] = { -1, -1, 1, 1, -2, -2, 2, 2 };
    int yDir[] = { -2, 2, -2, 2, -1, 1, -1, 1 };

    // Check all possible moves
    for (int i = 0; i < 8; i++)
    {
        int newX = position.x + xDir[i];
        int newY = position.y + yDir[i];

        Position newPos(newX, newY);

        // Check if the new position is within the board boundaries
        if (newPos.isInRange())
        {
            char pieceAtNewPosition = player.board[newY][newX];
            QString pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

            if (pieceAtNewPosition == ' ' || pieceAtNewPositionColor != this->color)
            {
                // Add the new position to the legal moves
                legalMoves.push_back(newPos);
            }
        }
    }

    return legalMoves;
}
