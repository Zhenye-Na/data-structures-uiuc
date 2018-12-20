/* Your code here! */
#ifndef _MAZE_
#define _MAZE_

#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"

using namespace cs225;

class SquareMaze
{

public:
  SquareMaze();
  void makeMaze(int w, int h);
  bool canTravel (int x, int y, int dir) const;
  void setWall (int x, int y, int dir, bool exists);
  vector<int> solveMaze ();
  PNG* drawMaze () const;
  PNG* drawMazeWithSolution ();
  void deleter(DisjointSets &d, int col, int row);

  PNG* drawCreativeMaze() const;
  PNG* drawCreativeMazeWithSolution();

  int dist(int a, int b, int c, int d) const;

private:
  struct cell {
    bool right = true;
    bool down = true;
    int x;
    int y;
    // int dist;
  };

  int width;
  int height;
  cell** maze;
  cell dest;
  // bool** visited;
};

#endif
