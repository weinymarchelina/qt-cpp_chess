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

#include "King.h"
#include <cctype>
#include "QDebug"
#include "player.h"

//Intent = Initialize a King object with the specified color and position.
//Pre = None.
//Pos = A King object is created with the given color and position.
King::King(bool isWhite, Position position)
{
    this->position = position;

    // Set the image URL and color based on the specified color
    if (isWhite) {
        this->imgUrl = ":/images/images/gKing.png";
        this->color = "WHITE";
    }
    else {
        this->imgUrl = ":/images/images/vKing.png";
        this->color = "BLACK";
    }
}

//Intent = Retrieve all possible moves for the King on the given board.
//Pre = A valid Board object 'gBoard' is provided.
//Pos = A QVector containing all legal moves for the King is returned.
QVector<Position> King::getPossibleMove(Board gBoard) {
    QVector<Position> legalMoves;

    // Create a Player object to access the board state
    Player player(gBoard.board);

    // Define the eight move directions
    int xDir[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int yDir[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // Check each eight directions
    for (int i = 0; i < 8; i++)
    {
        int newX = position.x + xDir[i];
        int newY = position.y + yDir[i];

        Position newPos(newX, newY);

        // Check if the new position is valid and not occupied by own piece
        if (newPos.isInRange())
        {
            // Check the piece at the new position
            char pieceAtNewPosition = player.getPieceAt(newPos);
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
                char piece = this->color == "WHITE" ? 'K' : 'k';
                int oldX = this->position.x;
                int oldY = this->position.y;

                // Update the temporary board with the new position
                tempBoard.board[newY][newX] = piece;
                tempBoard.board[oldY][oldX] = ' ';

                // Check if the player's king is under attack in the temporary board
                if (!player.isUnderAttack(pieceAtNewPositionColor, newPos, tempBoard))
                {
                    // Add the new position to the legal moves
                    legalMoves.push_back(newPos);
                }
            }
        }
    }

    return legalMoves;
}

//Intent = Move the King to the target position on the board.
//Pre = A valid Board object 'gBoard' is provided, and the target position is within the board boundaries.
//Pos = The King is moved to the target position on the board, and the last moved piece position is updated.
void King::move(Board& gBoard, Position targetPos)
{
    char currentPiece = this->color == "WHITE" ? 'K' : 'k';

    // Set the target position with the current piece
    gBoard.setPieceAt(targetPos, currentPiece);

    // Clear the current position
    gBoard.setPieceAt(this->position, ' ');

    // Update the last moved piece position
    gBoard.lastMovedPiecePosition = targetPos;

}

//Intent = Retrieve all possible moves for the King in a simulation.
//Pre = A valid Board object 'gBoard' is provided.
//Pos = A QVector containing all legal moves for the King in the simulation is returned.
QVector<Position> King::getSimulation(Board gBoard) {
    QVector<Position> legalMoves;    // Variable to be returned

    // Create a Player object to access the board state
    Player player(gBoard.board);

    // Define the eight move directions
    int xDir[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int yDir[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // Check each eight directions
    for (int i = 0; i < 8; i++)
    {
        // Get the new position
        int newX = position.x + xDir[i];
        int newY = position.y + yDir[i];

        Position newPos(newX, newY);

        // Check if the new position is valid and not occupied by own piece
        if (newPos.isInRange())
        {
            char pieceAtNewPosition = player.getPieceAt(newPos);
            QString pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

            if (pieceAtNewPosition == ' ' || pieceAtNewPositionColor != this->color)
            {
                legalMoves.push_back(newPos);
            }
        }
    }

    return legalMoves;
}
