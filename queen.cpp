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

#include "Queen.h"
#include <cctype>
#include "player.h"

// Intent: Create a Queen object with specified color and position.
// Pre: The color and position of the Queen are provided.
// Pos: Initializes the Queen object with the given color and position. Sets the image URL and color based on the color parameter.
Queen::Queen(bool isWhite, Position position)
{
    this->position = position;

    if (isWhite) {
        this->imgUrl = ":/images/images/gQueen.png";
        this->color = "WHITE";
    }
    else {
        this->imgUrl = ":/images/images/vQueen.png";
        this->color = "BLACK";
    }
}

// Intent: Get the possible legal moves for the Queen.
// Pre: The current state of the chessboard is provided.
// Pos: Returns a QVector of legal moves for the Queen based on the current state of the chessboard.
QVector<Position> Queen::getPossibleMove(Board gBoard)
{
    QVector<Position> legalMoves;
    Player player(gBoard.board);

    char piece = this->color == "WHITE" ? 'Q' : 'q';

    // Define the four diagonal directions
    int diagX[] = {-1, -1, 1, 1};
    int diagY[] = {-1, 1, -1, 1};

    // Check the diagonal directions
    for (int i = 0; i < 4; i++)
    {
        int newX = position.x + diagX[i];
        int newY = position.y + diagY[i];

        // Keep moving in the diagonal direction until out of bounds or obstruction
        while(Position(newX, newY).isInRange())
        {
            Position newPos(newX, newY);

            const char pieceAtNewPosition = player.getPieceAt(newPos);
            QString pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

            // If no piece at the position, add it as a legal move
            if (pieceAtNewPosition == ' ')
            {
                Board tempBoard;

                // Copy the current board state to the temporary board
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        tempBoard.board[row][col] = player.board[row][col];
                    }
                }


                int oldX = this->position.x;
                int oldY = this->position.y;

                tempBoard.board[newY][newX] = piece;
                tempBoard.board[oldY][oldX] = ' ';

                Position kingPos = player.getKingPosition(this->color);

                // Check if the move puts the King in check
                if (!player.isUnderAttack(this->color, kingPos, tempBoard))
                {
                    legalMoves.push_back(newPos);
                }
            }
            else if (pieceAtNewPositionColor != this->color)
            {
                Board tempBoard;

                // Copy the current board state to the temporary board
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        tempBoard.board[row][col] = player.board[row][col];
                    }
                }

                int oldX = this->position.x;
                int oldY = this->position.y;

                tempBoard.board[newY][newX] = piece;
                tempBoard.board[oldY][oldX] = ' ';

                Position kingPos = player.getKingPosition(this->color);

                // Check if the move puts the King in check
                if (!player.isUnderAttack(this->color, kingPos, tempBoard))
                {
                    legalMoves.push_back(newPos);
                }

                break;
            }
            else
            {
                break;
            }

            newX += diagX[i];
            newY += diagY[i];
        }
    }

    // Define the four straight directions
    int straightX[] = {-1, 1, 0, 0};
    int straightY[] = {0, 0, -1, 1};

    // Check the straight directions
    for (int i = 0; i < 4; i++)
    {
        int newX = position.x + straightX[i];
        int newY = position.y + straightY[i];

        // Keep moving in the straight direction until out of bounds or obstruction
        while (Position(newX, newY).isInRange())
        {
            Position newPos(newX, newY);

            char pieceAtNewPosition = player.getPieceAt(newPos);
            QString pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

            if (pieceAtNewPosition == ' ')
            {
                Board tempBoard;

                // Copy the current board state to the temporary board
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        tempBoard.board[row][col] = player.board[row][col];
                    }
                }


                int oldX = this->position.x;
                int oldY = this->position.y;

                tempBoard.board[newY][newX] = piece;
                tempBoard.board[oldY][oldX] = ' ';

                Position kingPos = player.getKingPosition(this->color);

                // Check if the move puts the King in check
                if (!player.isUnderAttack(this->color, kingPos, tempBoard))
                {
                    legalMoves.push_back(newPos);
                }
            }
            else if (pieceAtNewPositionColor != this->color)
            {
                Board tempBoard;

                // Copy the current board state to the temporary board
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        tempBoard.board[row][col] = player.board[row][col];
                    }
                }


                char piece = this->color == "WHITE" ? 'B' : 'b';
                int oldX = this->position.x;
                int oldY = this->position.y;

                tempBoard.board[newY][newX] = piece;
                tempBoard.board[oldY][oldX] = ' ';

                Position kingPos = player.getKingPosition(this->color);

                // Check if the move puts the King in check
                if (!player.isUnderAttack(this->color, kingPos, tempBoard))
                {
                    legalMoves.push_back(newPos);
                }

                break;
            }
            else
            {
                break;
            }

            newX += straightX[i];
            newY += straightY[i];
        }
    }

    return legalMoves;
}


// Intent: Move the Queen to the target position on the provided chessboard.
// Pre: The target position and the chessboard are provided.
// Pos: Moves the Queen to the target position on the chessboard and updates the last moved piece position.
void Queen::move(Board& gBoard, Position targetPos) {
    char currentPiece = this->color == "WHITE" ? 'Q' : 'q';

    gBoard.setPieceAt(targetPos, currentPiece);
    gBoard.setPieceAt(this->position, ' ');

    // Update the last moved piece position
    gBoard.lastMovedPiecePosition = targetPos;

}

// Intent: Get the possible legal moves for the Queen in a simulation.
// Pre: The current state of the chessboard is provided.
// Pos: Returns a QVector of legal moves for the Queen based on the current state of the chessboard in a simulation.
QVector<Position> Queen::getSimulation(Board gBoard) {
    QVector<Position> legalMoves;
    Player player(gBoard.board);

    char piece = this->color == "WHITE" ? 'Q' : 'q';

    // Define the four diagonal directions
    int diagX[] = {-1, -1, 1, 1};
    int diagY[] = {-1, 1, -1, 1};

    // Check the diagonal directions
    for (int i = 0; i < 4; i++) {
        int newX = position.x + diagX[i];
        int newY = position.y + diagY[i];

        // Keep moving in the diagonal direction until out of bounds or obstruction
        while (Position(newX, newY).isInRange()) {
            Position newPos(newX, newY);

            const char pieceAtNewPosition = player.getPieceAt(newPos);
            QString pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

            // If no piece at the position, add it as a legal move
            if (pieceAtNewPosition == ' ') {
                legalMoves.push_back(newPos);
            }
            else if (pieceAtNewPositionColor != this->color) {
                // If the piece at the position is of a different color, add it as a legal move and stop iterating in this direction
                legalMoves.push_back(newPos);
                break;
            }
            else {
                // If the piece at the position is of the same color, stop iterating in this direction
                break;
            }

            newX += diagX[i];
            newY += diagY[i];
        }
    }

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
                legalMoves.push_back(newPos);
            }
            else if (pieceAtNewPosition != ' ' && pieceAtNewPositionColor != this->color) {
                // If the piece at the position is of a different color, add it as a legal move and stop iterating in this direction
                legalMoves.push_back(newPos);
                break;
            }
            else {
                // If the piece at the position is of the same color, stop iterating in this direction
                break;
            }

            newX += straightX[i];
            newY += straightY[i];
        }
    }

    return legalMoves;
}
