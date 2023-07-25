#ifndef PLAYER_H
#define PLAYER_

#include "position.h"
#include "board.h"
#include <QString>
#include <QVector>
#include <cctype>

class Player
{
public:
    char board[8][8];
    Position lastMovedPiecePosition;
    Player(char (&board)[8][8]);
    QString getColor(char piece);
    char getPieceAt(Position pos);
    void setPieceAt(Position pos, char piece);
    QVector<Position> getEnemyPieces(QString color);
    QVector<Position> getOwnPieces(QString color);
    bool isUnderAttack(QString, Position, Board);
    Position getKingPosition(QString);
    bool isCheckMate(QString color, Position kingPos, Board gBoard);
};

#endif // PLAYER_H
