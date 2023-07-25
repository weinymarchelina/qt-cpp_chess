#ifndef BOARD_H
#define BOARD_H

#include "position.h"
#include <QString>
#include <QVector>

class Board
{
public:
    char board[8][8];
    Position lastMovedPiecePosition;
    Board();
    void setPieceAt(Position pos, char piece);
};

#endif // BOARD_H
