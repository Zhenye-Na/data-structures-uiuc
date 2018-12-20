#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
  SquareMaze m;
  m.makeMaze(30, 60);

  PNG* maze = m.drawCreativeMazeWithSolution();
  maze->writeToFile("creative.png");

  delete maze;
  return 0;
}
