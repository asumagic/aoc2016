#include "common.hpp"

void rotate(Direction &dir, bool right) // caca
{
    if (right && (dir == West))
        dir = North;
    else if (!right && (dir == North))
        dir = West;
    else
        dir = static_cast<Direction>(static_cast<int>(dir) + (right ? 1 : -1));
}

Position advance_by(Position pos, const Direction dir, const int steps)
{
    switch (dir)
    {
    case North: pos.y -= steps; break;
    case East:  pos.x += steps; break;
    case South: pos.y += steps;	break;
    case West:  pos.x -= steps; break;
    }

    return pos;
}
