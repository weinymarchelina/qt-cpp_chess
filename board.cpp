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

#include "board.h"
#include "knight.h"
#include "rook.h"
#include "king.h"
#include "bishop.h"
#include "queen.h"
#include "pawn.h"
#include <QVector>
#include <cctype>

// Intent: Create a Board object with the initial configuration of a chessboard.
// Pre: None.
// Post: Initializes the board array with the initial pieces on a chessboard.
Board::Board()
{
    // Define the initial configuration of the chessboard
    char initialBoard[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    // Copy the initialBoard values to the board array
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            this->board[i][j] = initialBoard[i][j];
        }
    }
}

// Intent: To set a specific piece at a given position on the board.
// Pre: The position should be valid within the board boundaries and the piece should be a valid character representing the desired piece.
// Post: The piece is successfully placed at the specified position on the board.
void Board::setPieceAt(Position pos, char piece) {
    this->board[pos.y][pos.x] = piece;
}
