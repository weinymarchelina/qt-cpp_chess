#ifndef ROOK_H
#define ROOK_H


#include <QString>
#include <QVector>
#include "Position.h"
#include "board.h"

class Rook
{
public:
    Position position;
    QString color;
    QString imgUrl;
    Rook(bool, Position);
    QVector<Position> getPossibleMove(Board gBoard);
    void move(Board& gBoard, Position targetPos);
    QVector<Position> getSimulation(Board gBoard);
};


#endif // ROOK_H
