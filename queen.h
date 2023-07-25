#ifndef QUEEN_H
#define QUEEN_H

#include <QString>
#include <QVector>
#include "Position.h"
#include "QDebug"
#include "board.h"

class Queen
{
public:
    Position position;
    QString color;
    QString imgUrl;

    Queen(bool, Position);
    QVector<Position> getPossibleMove(Board gBoard);
    void move(Board& gBoard, Position targetPos);
    QVector<Position> getSimulation(Board gBoard);
};


#endif // QUEEN_H
