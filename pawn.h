#ifndef PAWN_H
#define PAWN_H

#include <QString>
#include <QVector>
#include "Position.h"
#include "board.h"

class Pawn
{
public:
    Pawn(bool isWhite, Position position);
    Position position;
    QString color;
    QString imgUrl;
    bool isMoveTwoRow;
    bool isAbleEnPassant(Position targetPos, Board gBoard);
    QVector<Position> getPossibleMove(Board board);
    void move(Board& gBoard, Position targetPos);
    QVector<Position> getSimulation(Board gBoard);

};

#endif // PAWN_H
