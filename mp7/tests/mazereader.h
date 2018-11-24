#ifndef MAZEREADER_H
#define MAZEREADER_H

#include <stdint.h>
#include <vector>
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

using namespace cs225;

// Avoid students predefined macros messing up our enums
#undef NOWALLS
#undef RIGHTWALL
#undef DOWNWALL
#undef BOTHWALLS
#undef RIGHT
#undef DOWN
#undef LEFT
#undef UP

using namespace std;

class MazeReader
{
	public:
	enum wall_t
	{
		NOWALLS   = 0x0,
		RIGHTWALL = 0x1,
		DOWNWALL  = 0x2,
		BOTHWALLS = RIGHTWALL | DOWNWALL
	};
	enum dir_t
	{
		RIGHT = 0,
		DOWN  = 1,
		LEFT  = 2,
		UP    = 3
	};

	private:
	int width;
	int height;
	vector<uint8_t> walls;
	vector<dir_t> solution;
	int destination_x;
	int destination_y;

	public:
	MazeReader(const PNG & image);
	bool isWall(int x, int y, wall_t wall) const { return (walls[y*height + x] & wall) != 0; }
	bool isWallInDir(int x, int y, int dir) const;
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getDestinationX() const { return destination_x; }
	int getDestinationY() const { return destination_y; }
	size_t getSolutionSize() const { return solution.size(); }
	dir_t getSolutionAt(size_t index) const { return solution[index]; }
};

#endif
