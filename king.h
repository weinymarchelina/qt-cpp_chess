#ifndef KING_H
#define KING_H

#include <QString>
#include <QVector>
#include "Position.h"
#include "board.h"

class King
{
public:
    Position position;
    QString color;
    QString imgUrl;

    King(bool, Position);
    QVector<Position> getPossibleMove(Board gBoard);
    void move(Board& gBoard, Position targetPos);
    QVector<Position> getSimulation(Board gBoard);
};

#endif // KING_H
