#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
    int x, y;
    Position();
    Position(int, int);
    bool isInRange();
    bool operator==(const Position& pos);
};

#endif // POSITION_H
