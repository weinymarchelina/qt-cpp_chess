#ifndef BISHOP_H
#define BISHOP_H

#include <QString>
#include <QVector>
#include "Position.h"
#include "Board.h"

class Bishop
{
public:
    Position position;
    QString color;
    QString imgUrl;

    Bishop(bool, Position);
    QVector<Position> getPossibleMove(Board board);
    void move(Board& gBoard, Position targetPos);
    QVector<Position> getSimulation(Board gBoard);
};


#endif // BISHOP_H
