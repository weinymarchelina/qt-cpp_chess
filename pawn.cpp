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

#include "pawn.h"
#include <cctype>
#include <QDebug>
#include "player.h"

// Intent = Initialize a Pawn object with the given parameters.
// Pre = The 'isWhite' parameter indicates whether the pawn is white or black. The 'position' //parameter specifies the initial position of the pawn on the board.
// Pos = The Pawn object is initialized with the specified parameters.
Pawn::Pawn(bool isWhite, Position position)
{
    // Set the position of the pawn
    this->position = position;
    // Initialize the 'isMoveTwoRow' flag as false
    this->isMoveTwoRow = false;

    if (isWhite)
    {
        // Set the image URL and color for a white pawn
        this->imgUrl = ":/images/images/gPawn.png";
        this->color = "WHITE";

        // Check if the pawn is in the starting position for a white pawn
        if (position.y != 6)
        {
            this->isMoveTwoRow = true;
        }
    }
    else
    {
        // Set the image URL and color for a black pawn
        this->imgUrl = ":/images/images/vPawn.png";
        this->color = "BLACK";

        // Check if the pawn is in the starting position for a black pawn
        if (position.y != 1)
        {
            this->isMoveTwoRow = true;
        }
    }
}

// Intent: Get all possible moves for a pawn.
// Pre: The 'gBoard' parameter represents the current state of the chessboard.
// Pos: Returns a vector of positions representing all legal moves for the pawn.
QVector<Position> Pawn::getPossibleMove(Board gBoard)
{
    QVector<Position> legalMoves;

    // Create a Player object to access the board state
    Player player(gBoard.board);

    int direction = 0;
    char piece = ' ';

    // Determine the direction and piece type based on the pawn's color
    if (this->color == "WHITE")
    {
        direction = -1;
        piece = 'P';
    }
    else if (this->color == "BLACK")
    {
        direction = 1;
        piece = 'p';
    }

    // Calculate the new position of the pawn
    int newY = this->position.y + direction;
    Position newPos = Position(this->position.x, newY);

    // Get the piece at the new position and its color
    char pieceAtNewPosition = player.getPieceAt(newPos);
    QString pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

    // Check if the new position is within the board boundaries and if it is empty
    if ((newPos.isInRange()) && player.getPieceAt(newPos) == ' ')
    {
        // Create a temporary board to simulate the move
        Board tempBoard;
        for (int row = 0; row < 8; row++)
        {
            for (int col = 0; col < 8; col++)
            {
                tempBoard.board[row][col] = player.board[row][col];
            }
        }

        int oldX = this->position.x;
        int oldY = this->position.y;

        // Update the temporary board with the pawn's move
        tempBoard.board[newY][oldX] = piece;
        tempBoard.board[oldY][oldX] = ' ';

        // Get the position of the player's king
        Position kingPos = player.getKingPosition(this->color);

        // Check if the player's king is still in check after the move
        if (!player.isUnderAttack(this->color, kingPos, tempBoard))
        {
            legalMoves.push_back(newPos);

            int newerY = newY + direction;
            Position newerPos = Position(this->position.x, newerY);

            // Check if the pawn can move two squares from the starting position
            if (!this->isMoveTwoRow && player.getPieceAt(newerPos) == ' ')
            {
                for (int row = 0; row < 8; row++)
                {
                    for (int col = 0; col < 8; col++)
                    {
                        tempBoard.board[row][col] = player.board[row][col];
                    }
                }

                tempBoard.board[newerY][oldX] = piece;
                tempBoard.board[oldY][oldX] = ' ';

                Position kingPos = player.getKingPosition(this->color);

                // Get the piece at the new position and its color
                pieceAtNewPosition = player.getPieceAt(newerPos);
                pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

                // Check if the player's king is still in check after the move
                if (!player.isUnderAttack(this->color, kingPos, tempBoard))
                {
                    legalMoves.push_back(Position(position.x, newY + direction));
                }
            }
        }
    }

    // Check if the pawn can capture diagonally
    int captureX[] = { this->position.x - 1, this->position.x + 1 };

    // Iterates two times to check the top left and top right
    for (int i = 0; i < 2; i++)
    {
        // Set the current captureX with the newY as the new position
        int newX = captureX[i];
        Position newPos = Position(newX, newY);

        // If the newPos is in range
        if (newPos.isInRange())
        {
            // Make sure that the piece on the top left and top right is the enemy piece
            pieceAtNewPosition = player.getPieceAt(newPos);
            pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

            if (pieceAtNewPosition != ' ' && pieceAtNewPositionColor != this->color)
            {
                // Simulate the newPos on the temporary board
                Board tempBoard;
                for (int row = 0; row < 8; row++)
                {
                    for (int col = 0; col < 8; col++)
                    {
                        tempBoard.board[row][col] = player.board[row][col];
                    }
                }

                int oldX = this->position.x;
                int oldY = this->position.y;

                tempBoard.board[newY][newX] = piece;
                tempBoard.board[oldY][oldX] = ' ';

                // If the newPos doesn't make the king on check, then add it to the legalMoves
                Position kingPos = player.getKingPosition(this->color);
                if (!player.isUnderAttack(this->color, kingPos, tempBoard))
                {
                    legalMoves.push_back(newPos);
                }
            }
        }
    }

    // Return the legal moves
    return legalMoves;
}

// Intent: To check whether a Pawn can do the en passant move.
// Pre: The 'gBoard' parameter represents the current state of the chessboard and the 'targetPos' parameter represents the designated position.
// Pos: Returns true if the en passant move can be made, and return false if not.
bool Pawn::isAbleEnPassant(Position targetPos, Board gBoard)
{
    // If the color is white, the correct y position is 2 and if the color is black the correct y position is 5
    int correctY = (this->color == "WHITE") ? 2 : 5;

    // If the y target position is not correct, then the en passant move can't be made
    if (targetPos.y != correctY)
    {
        return false;
    }

    // Check whether the last moved piece is on the top right or top left of the current pawn
    if (gBoard.lastMovedPiecePosition.x == targetPos.x && abs(gBoard.lastMovedPiecePosition.y - targetPos.y) == 1)
    {
        // Copy the lastMovedPiece on the board to the local variable
        char lastMovedPiece = gBoard.board[gBoard.lastMovedPiecePosition.y][gBoard.lastMovedPiecePosition.x];

        // Check if the last moved piece is a pawn or not
        if (lastMovedPiece == 'P' || lastMovedPiece == 'p')
        {
            // Construct a new pawn with the position of the last moved position
            bool isWhite = lastMovedPiece == 'P' ? true : false;
            Pawn lastMovedPawn(isWhite, gBoard.lastMovedPiecePosition);

            // If the last moved pawn just move two row, return else
            if (lastMovedPawn.isMoveTwoRow)
            {
                return true;
            }
        }
    }

    // Return false if the true condition not fullfilled
    return false;
}

// Intent: Move the pawn to the target position on the board.
// Pre: The target position is a valid position on the board, and the board reference is provided.
// Pos: The pawn is moved to the target position on the board, and the last moved piece position is updated.
void Pawn::move(Board& gBoard, Position targetPos)
{
    // If the color is white set the current icon to P, if it is black set it to p
    char currentPiece = this->color == "WHITE" ? 'P' : 'p';

    // Move the board by set the pawn at the new position and set the previous position to ' ' and update the lastMovedPosition
    gBoard.setPieceAt(targetPos, currentPiece);
    gBoard.setPieceAt(this->position, ' ');
    gBoard.lastMovedPiecePosition = targetPos;
}

// Intent: Get all possible moves for a pawn but do not do a simulation like the getPossibleMoves method.
// Pre: The 'gBoard' parameter represents the current state of the chessboard.
// Pos: Returns a vector of positions representing all legal moves for the pawn in a simulation.
QVector<Position> Pawn::getSimulation(Board gBoard)
{
    QVector<Position> legalMoves;

    // Create a Player object to access the board state
    Player player(gBoard.board);

    int direction = 0;
    char piece = ' ';

    // Determine the direction and piece type based on the pawn's color
    if (this->color == "WHITE")
    {
        direction = -1;
        piece = 'P';

    }
    else if (this->color == "BLACK")
    {
        direction = 1;
        piece = 'p';
    }

    // Calculate the new position of the pawn
    int newY = this->position.y + direction;
    Position newPos = Position(this->position.x, newY);

    // Get the piece at the new position and its color
    char pieceAtNewPosition = player.getPieceAt(newPos);
    QString pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

    // Check if the new position is within the board boundaries and if it is empty
    if ((newPos.isInRange()) && player.getPieceAt(newPos) == ' ')
    {
        legalMoves.push_back(Position(position.x, newY + direction));

        int newerY = newY + direction;
        Position newerPos = Position(this->position.x, newerY);

        // Check if the pawn can move two squares from the starting position
        if (!this->isMoveTwoRow && player.getPieceAt(newerPos) == ' ')
        {
            legalMoves.push_back(Position(position.x, newY + direction));
        }
    }

    // Check if the pawn can capture diagonally
    int captureX[] = { this->position.x - 1, this->position.x + 1 };
    for (int i = 0; i < 2; i++)
    {
        int newX = captureX[i];
        Position newPos = Position(newX, newY);

        // Check if the diagonal positions are still in range
        if (newPos.isInRange())
        {
            // If the piece on the top right and top left is the enemy piece, appends it to the legalMoves
            pieceAtNewPosition = player.getPieceAt(newPos);
            pieceAtNewPositionColor = player.getColor(pieceAtNewPosition);

            if (pieceAtNewPosition != ' ' && pieceAtNewPositionColor != this->color)
            {
                legalMoves.push_back(newPos);
            }
        }
    }

    return legalMoves;  // Return the legalMoves
}
