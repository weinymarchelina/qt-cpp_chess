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

#include "position.h"

// Intent: Create a Position object with default values.
// Pre: None.
// Pos: Initializes the x and y coordinates of the Position object to 0.
Position::Position()
{
    this->x = 0;
    this->y = 0;
}
// Intent: Create a Position object with specified coordinates.
// Pre: The x and y coordinates are provided.
// Pos: Initializes the x and y coordinates of the Position object to the provided values.
Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}


// Intent: Check if the position is within the valid range of the chessboard.
// Pre: None.
// Pos: Returns true if the position is within the range [0, 7] for both x and y coordinates, false otherwise.
bool Position::isInRange()
{
    if (this->x < 0 || this->x > 7 || this->y < 0 || this->y > 7) {
        return false;
    }

    return true;
}

// Intent: Compare two Position objects for equality.
// Pre: A Position object is provided for comparison.
// Pos: Returns true if the x and y coordinates of both Position objects are equal, false otherwise.
bool Position::operator==(const Position& pos)
{
    if(this->x == pos.x && this->y == pos.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
