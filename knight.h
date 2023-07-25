#ifndef KNIGHT_H
#define KNIGHT_H

#include <QString>
#include <QVector>
#include "Position.h"
#include "Board.h"

class Knight
{
public:
    Position position;
    QString color;
    QString imgUrl;

    Knight(bool, Position);
    QVector<Position> getPossibleMove(Board board);
    void move(Board& board, Position targetPos);
    QVector<Position> getSimulation(Board gBoard);
};

#endif // KNIGHT_H
