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

#include "Bishop.h"
#include "player.h"
#include <cctype>
#include <board.h>
#include <QDebug>

//Intent = Initialize a Bishop object with the specified color and position.
//Pre = None.
//Pos = A Bishop object is created with the given color and position.
Bishop::Bishop(bool isWhite, Position position)
{
    this->position = position;
    // Set the image URL and color based on the specified color
    if (isWhite) {
        this->imgUrl = ":/images/images/gBishop.png";
        this->color = "WHITE";
    }
    else {
        this->imgUrl = ":/images/images/vBishop.png";
        this->color = "BLACK";
    }
}


//Intent = Retrieve all possible moves for the Bishop on the given board.
//Pre = A valid Board object 'gBoard' is provided.
//Pos = A QVector containing all legal moves for the Bishop is returned.
QVector<Position> Bishop::getPossibleMove(Board gBoard) {
    QVector<Position> legalMoves;

    // Create a Player object to access the board state
    Player player(gBoard.board);

    // Define the diagonal directions: up-left, up-right, down-left, down-right
    int xDir[] = {1, -1, 1, -1};
    int yDir[] = {-1, -1, 1, 1};

    // Check all diagonal directions
    for (int i = 0; i < 4; i++)
    {
        int newX = position.x + xDir[i];
        int newY = position.y + yDir[i];

        // Continue checking the diagonal until out of range
        while(Position(newX, newY).isInRange())
        {
            Position newPos(newX, newY);

            // Check the piece at the new position
            const char pieceAtNewPosition = player.getPieceAt(newPos);
            QString pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

            if (pieceAtNewPosition == ' ')
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
                char piece = this->color == "WHITE" ? 'B' : 'b';
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
            else if (pieceAtNewPositionColor != this->color)
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
                char piece = this->color == "WHITE" ? 'B' : 'b';
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

                // Break the loop as the bishop cannot move beyond a piece of the opposite color
                break;
            }
            else
            {
                // Break the loop as the bishop cannot move beyond a piece of the same color
                break;
            }

            newX += xDir[i];
            newY += yDir[i];
        }
    }

    return legalMoves;
}

//Intent = Move the Bishop to the target position on the board.
//Pre = A valid Board object 'gBoard' is provided, and the target position is within the board boundaries.
//Pos = The Bishop is moved to the target position on the board, and the last moved piece position is updated.
void Bishop::move(Board& gBoard, Position targetPos) {
    char currentPiece = this->color == "WHITE" ? 'B' : 'b';

    gBoard.setPieceAt(targetPos, currentPiece);
    gBoard.setPieceAt(this->position, ' ');
    gBoard.lastMovedPiecePosition = targetPos;
}

//Intent = Retrieve all possible moves for the Bishop in a simulation.
//Pre = A valid Board object 'gBoard' is provided.
//Pos = A QVector containing all legal moves for the Bishop in the simulation is returned.
QVector<Position> Bishop::getSimulation(Board gBoard) {
    QVector<Position> legalMoves;

    // Create a Player object to access the board state
    Player player(gBoard.board);

    // Define the diagonal directions: up-left, up-right, down-left, down-right
    int xDir[] = {1, -1, 1, -1};
    int yDir[] = {-1, -1, 1, 1};

    // Check all diagonal directions
    for (int i = 0; i < 4; i++)
    {
        int newX = position.x + xDir[i];
        int newY = position.y + yDir[i];

        // Continue checking the diagonal until out of range
        while(Position(newX, newY).isInRange())
        {
            Position newPos(newX, newY);

            // Check the piece at the new position
            const char pieceAtNewPosition = player.getPieceAt(newPos);
            QString pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

            if (pieceAtNewPosition == ' ')
            {
                // Add the new position to the legal moves
                legalMoves.push_back(newPos);
            }
            else if (pieceAtNewPosition != ' ' && pieceAtNewPositionColor != this->color)
            {
                // Add the new position to the legal moves
                legalMoves.push_back(newPos);

                // Break the loop as the bishop cannot move beyond a piece of the opposite color
                break;
            }
            else
            {
                // Break the loop as the bishop cannot move beyond a piece of the same color
                break;
            }

            newX += xDir[i];
            newY += yDir[i];
        }
    }

    return legalMoves;
}

