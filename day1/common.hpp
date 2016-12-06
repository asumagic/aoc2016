#ifndef COMMON_HPP
#define COMMON_HPP

#define PART2

enum Direction
{
	North = 0,
	East,
	South,
	West
};

struct Position
{
	int x = 0, y = 0;

	bool operator==(const Position other) { return (x == other.x) && (y == other.y); }
};

void rotate(Direction& dir, bool right);
Position advance_by(Position pos, const Direction dir, const int steps);

#endif // COMMON_HPP
