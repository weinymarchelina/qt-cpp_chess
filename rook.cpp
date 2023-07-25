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

#include "Rook.h"
#include <cctype>
#include <QDebug>
#include "player.h"

// Intent: Create a Rook object with the specified color and position.
// Pre: The color (isWhite) and position of the Rook are provided.
// Pos: Initializes the Rook object with the specified color, position, and image URL.
Rook::Rook(bool isWhite, Position position) {
    this->position = position;

    // Set the image URL and color based on the specified color
    if (isWhite) {
        this->imgUrl = ":/images/images/gRook.png";
        this->color = "WHITE";
    }
    else {
        this->imgUrl = ":/images/images/vRook.png";
        this->color = "BLACK";
    }
}

// Intent: Get the possible legal moves for the Rook on the provided chessboard.
// Pre: The current state of the chessboard is provided.
// Pos: Returns a QVector of legal moves for the Rook based on the current state of the chessboard.
QVector<Position> Rook::getPossibleMove(Board gBoard) {
    QVector<Position> legalMoves;
    Player player(gBoard.board);

    // Define the four straight directions
    int straightX[] = {-1, 1, 0, 0};
    int straightY[] = {0, 0, -1, 1};

    // Check the straight directions
    for (int i = 0; i < 4; i++) {
        int newX = position.x + straightX[i];
        int newY = position.y + straightY[i];

        // Keep moving in the straight direction until out of bounds or obstruction
        while (Position(newX, newY).isInRange()) {
            Position newPos(newX, newY);

            char pieceAtNewPosition = player.getPieceAt(newPos);
            QString pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

            if (pieceAtNewPosition == ' ') {
                // Create a temporary board to simulate the move
                Board tempBoard;

                // Copy the current state of the board to the temporary board
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        tempBoard.board[row][col] = player.board[row][col];
                    }
                }

                char piece = this->color == "WHITE" ? 'R' : 'r';
                int oldX = this->position.x;
                int oldY = this->position.y;

                // Simulate the move on the temporary board
                tempBoard.board[newY][newX] = piece;
                tempBoard.board[oldY][oldX] = ' ';

                // Get the position of the King of the same color
                Position kingPos = player.getKingPosition(this->color);

                // Check if the King is not under attack after the move
                if (!player.isUnderAttack(this->color, kingPos, tempBoard)) {
                    legalMoves.push_back(newPos);
                }
            }
            else if (pieceAtNewPositionColor != this->color) {
                // Create a temporary board to simulate the move
                Board tempBoard;

                // Copy the current state of the board to the temporary board
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        tempBoard.board[row][col] = player.board[row][col];
                    }
                }

                char piece = this->color == "WHITE" ? 'B' : 'b';
                int oldX = this->position.x;
                int oldY = this->position.y;

                // Simulate the move on the temporary board
                tempBoard.board[newY][newX] = piece;
                tempBoard.board[oldY][oldX] = ' ';

                // Get the position of the King of the same color
                Position kingPos = player.getKingPosition(this->color);

                // Check if the King is not under attack after the move
                if (!player.isUnderAttack(this->color, kingPos, tempBoard)) {
                    legalMoves.push_back(newPos);
                }

                break;
            }
            else {
                // If there is a piece of the same color, stop iterating in this direction
                break;
            }

            newX += straightX[i];
            newY += straightY[i];
        }
    }

    return legalMoves;
}

// Intent: Move the Rook to the target position on the provided chessboard.
// Pre: The chessboard (gBoard) and the target position are provided.
// Pos: Updates the chessboard by moving the Rook to the target position and updates the last moved piece position.
void Rook::move(Board& gBoard, Position targetPos)
{
    // Determine the current piece character based on the color of the Rook.
    char currentPiece = this->color == "WHITE" ? 'R' : 'r';

    // Set the target position on the chessboard to the current piece character.
    gBoard.setPieceAt(targetPos, currentPiece);

    // Set the current position of the Rook on the chessboard to an empty space.
    gBoard.setPieceAt(this->position, ' ');

    // Update the last moved piece position to the target position.
    gBoard.lastMovedPiecePosition = targetPos;

}

// Intent: Get the legal moves for the Rook in a simulation of the provided chessboard.
// Pre: The current state of the chessboard is provided.
// Pos: Returns a QVector of legal moves for the Rook based on the current state of the chessboard.
QVector<Position> Rook::getSimulation(Board gBoard) {
    QVector<Position> legalMoves;
    Player player(gBoard.board);

    // Define the possible straight directions
    int straightX[] = {-1, 1, 0, 0};
    int straightY[] = {0, 0, -1, 1};

    // Check the straight directions
    for (int i = 0; i < 4; i++) {
        int newX = position.x + straightX[i];
        int newY = position.y + straightY[i];

        // Keep moving in the straight direction until out of bounds or obstruction
        while (Position(newX, newY).isInRange()) {
            Position newPos(newX, newY);

            // Get the piece color at the new position
            char pieceAtNewPosition = player.getPieceAt(newPos);
            QString pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

            if (pieceAtNewPosition == ' ') {
                legalMoves.push_back(newPos);
            }
            else if (pieceAtNewPosition != ' ' && pieceAtNewPositionColor != this->color) {
                legalMoves.push_back(newPos);

                break; // Stop checking in this direction after capturing an opponent's piece
            }
            else {
                break; // Stop checking in this direction if there is an obstruction
            }

            newX += straightX[i];
            newY += straightY[i];
        }
    }

    return legalMoves;


}


