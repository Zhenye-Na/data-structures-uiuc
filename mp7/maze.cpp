#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>
#include "maze.h"
#include <math.h>

SquareMaze::SquareMaze():width(0), height(0){}

/**
 * Attempts to delete both bottom and right walls of a cell
 * doesnt delete if edge case or if would cause a cycle
 */
void SquareMaze::deleter(DisjointSets &d, int col, int row)
{
  // delete right if possible
  if (col < (width - 1) && d.find(row * width + col) != d.find(row * width + col + 1)) {
    maze[col][row].right = false;
    d.setunion(row * width + col, row * width + col + 1);
  }

  // delete bottom wall if possible
  if (row < (height - 1) && d.find(row * width + col) != d.find((row + 1) * width + col)) {
    maze[col][row].down = false;
    d.setunion(row * width + col, (row + 1) * width + col);
  }
}

/**
 * Creates maze by assigning each cell in the array a number
 * randomly shuffles numbers and then sequentially goes through shuffled numbers
 * deletes as many walls as possible of each cell
 */
void SquareMaze::makeMaze(int w, int h)
{
  // delete allocated memory if maze already exists
  if (width != 0) {
    for(int i = 0; i < width; i++) {
      delete maze[i];
    }
    delete[] maze;
  }

  width = w;
  height = h;
  maze = new cell*[width];
  DisjointSets d;
  int r;
  vector<int> arr;

  // initialize maze and visited 2d arrays
  for(int i = 0; i < width; i++){
    maze[i] = new cell[height];
  }

  // add each cell to a disjoint set
  d.addelements(width*height);

  // iterate through array and use helper function to delete random walls while
  // preventing cycles
  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      maze[i][j].x = i;
      maze[i][j].y = j;

      arr.push_back(j * width + i);
    }
  }

  struct timeval time;
  gettimeofday(&time, NULL);
  srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

  random_shuffle(arr.begin(), arr.end());

  int temp = arr[0];

  int currx;
  int curry;

  for(unsigned i = 0; i < arr.size(); i++){
    currx  = arr[i] % width;
    curry = arr[i] / width;
    deleter(d, currx, curry);
  }
}

/**
 * Checks if a wall exists in the direction wishing to traversal
 * also checks if edge case of traveling over dimensions
 */
bool SquareMaze::canTravel(int x, int y, int dir) const
{
  if (dir == 0)
    if (!maze[x][y].right)
      return true;

  if (dir == 1)
    if (!maze[x][y].down)
      return true;

  if (dir == 2 && x-1 >= 0)
    if (!maze[x-1][y].right)
      return true;

  if (dir == 3 && y-1 >= 0)
    if (!maze[x][y-1].down)
      return true;

  return false;
}

/**
 * Decides to set a wall at the specified location
 */
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
  if (dir == 0)
    maze[x][y].right = exists;

  if(dir == 1)
    maze[x][y].down = exists;

  return;
}

/**
 * Solves maze using bfs
 */
vector<int> SquareMaze::solveMaze()
{
  queue<cell> q;
  vector<int> bottomRow;
  vector<int> ret;
  vector<cell> parent;
  cell curr;
  int x = 0;
  int y = 0;
  int dist = 0;
  bool** visited = new bool*[width];

  bottomRow.reserve(width);
  parent.reserve(width*height);
  for (int i = 0; i < width; i++) {
    visited[i] = new bool[height];
    for(int j = 0; j < height; j++)
      visited[i][j] = false;
  }

  // push the starting cell (origin) onto queue and mark as visisted
  q.push(maze[x][y]);
  visited[x][y] = true;

  // bfs traversal
  while (!q.empty()) {
    curr = q.front();
    q.pop();
    x = curr.x;
    y = curr.y;

    if (y == (height - 1))
      bottomRow[x] = dist;

    if (canTravel(x, y, 0) && !visited[x + 1][y]) {
      q.push(maze[x + 1][y]);
      visited[x + 1][y] = true;
      parent[y * width + x + 1] = curr;
    }

    if (canTravel(x, y, 1) && !visited[x][y + 1]) {
      q.push(maze[x][y + 1]);
      visited[x][y + 1] = true;
      parent[(y + 1) * width + x] = curr;
    }

    if (canTravel(x, y, 2) && !visited[x-1][y]) {
      q.push(maze[x-1][y]);
      visited[x-1][y] = true;
      parent[y*width + x-1] = curr;
    }

    if (canTravel(x, y, 3) && !visited[x][y-1]) {
      q.push(maze[x][y - 1]);
      visited[x][y - 1] = true;
      parent[(y - 1) * width + x] = curr;
    }

    dist++;
  }

  // find which cell in the bottom row is furthest (path-wise) from origin
  int maxDist = 0;
  int destX;
  for(int i = 0; i < width; i++) {
    if(bottomRow[i] > maxDist) {
      maxDist = bottomRow[i];
      destX = i;
    }
  }

  dest = maze[destX][height-1];
  curr = dest;
  cell par;
  int dir;

  // use parent vector to backtrack from dest to
  // origin and insert directions into return vector
  while(!(curr.x == 0 && curr.y == 0)) {
    par = parent[(curr.y) * width + curr.x];

    if (par.x == curr.x) {
      if (par.y + 1 == curr.y)
        dir = 1;

      if (par.y - 1 == curr.y)
        dir = 3;
    }

    if (par.y == curr.y) {
      if (par.x + 1 == curr.x)
        dir = 0;

      if (par.x - 1 == curr.x)
        dir = 2;
    }

    ret.insert(ret.begin(), dir);
    curr = par;
  }

  for(int i = 0; i < width; i++)
    delete visited[i];
  delete[] visited;

  return ret;

}

/**
 * Draws maze using specified formulas in doxygen
 */
PNG* SquareMaze::drawMaze() const
{
  PNG* ret = new PNG(width * 10 + 1, height * 10 + 1);

  for (unsigned i = 10; i < ret->width(); i++){
    HSLAPixel & p = ret->getPixel(i, 0);
    p.l = 0;
  }

  for (unsigned i = 0; i < ret->height(); i++){
    HSLAPixel & p = ret->getPixel(0, i);
    p.l = 0;
  }

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {

      if (maze[i][j].right){
        for(int k = 0; k <= 10; k++){
          HSLAPixel & p = ret->getPixel((i + 1) * 10, j * 10 + k);
          p.l = 0;
        }
      }

      if (maze[i][j].down){
        for (int k = 0; k <= 10; k++){
          HSLAPixel & p = ret->getPixel(i * 10 + k, (j + 1) * 10);
          p.l = 0;
        }
      }

    }
  }

  return ret;
}

/**
 * Draws maze with solution using specified formula in doxygen
 */
PNG* SquareMaze::drawMazeWithSolution()
{
  PNG *ret = drawMaze();
  vector<int> path = solveMaze();

  HSLAPixel red (0,1,0.5,1);

  int currx = 5;
  int curry = 5;
  int counter;

  for (unsigned i = 0; i < path.size(); i++) {

    counter = 0;

    if (path[i] == 0) {
      while (counter < 10) {
        ret->getPixel(currx + counter, curry) = red;
        counter++;
      }

      currx += counter;
    }

    else if (path[i] == 1) {
      while (counter < 10) {
        ret->getPixel(currx, curry + counter) = red;
        counter++;
      }

      curry += counter;
    }

    else if (path[i] == 2) {
      while (counter < 10) {
        ret->getPixel(currx - counter, curry) = red;
        counter++;
      }

      currx -= counter;
    }

    else if (path[i] == 3) {
      while (counter < 10) {
        ret->getPixel(currx, curry - counter) = red;
        counter++;
      }

      curry -= counter;
    }
  }

  ret->getPixel(currx, curry) = red;

  dest.down = false;
  maze[dest.x][dest.y].down = false;

  for (int k = 1; k <= 9; k++) {
    ret->getPixel(dest.x * 10 + k, (dest.y + 1) * 10).l = 1.0;
  }

  return ret;
}



/**
 * Draw creative maze
 */
PNG* SquareMaze::drawCreativeMaze() const
{
  PNG* ret = new PNG(width * 10 + 1, height * 10 + 1);

  HSLAPixel purple (277,1.0, 0.31, 1.0);

  for (unsigned i = 10; i < ret->width(); i++) {
    // INSERT COLOR OF TOP BORDER
    ret->getPixel(i, 0) = purple;
  }

  for (unsigned i = 0; i < ret->height(); i++) {
    // INSERT COLOR OF LEFT BORDER
    ret->getPixel(0, i) = purple;
  }

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {

      HSLAPixel wall ( dist(i, j, width, height), 1, 0.74, 1);

      if (maze[i][j].right) {
        for (int k = 0; k<=10; k++) {
           // INSERT COLOR OF WALL
           ret->getPixel((i + 1) * 10, j * 10 + k) = wall;
        }
      }

      if (maze[i][j].down) {
        for (int k = 0; k <= 10; k++) {
          // INSERT COLOR OF WALL
          ret->getPixel(i * 10 + k, (j + 1) * 10) = wall;
        }
      }

    }
  }

  for (unsigned i = 0; i < ret->width(); i++){
    // INSERT COLOR OF BOTTOM BORDER
    ret->getPixel(i, ret->height() - 1) = purple;
  }

  for (unsigned i = 0; i < ret->height(); i++){
    // INSERT COLOR OF RIGHT BORDER
    ret->getPixel(ret->width() - 1, i) = purple;
  }

  return ret;
}

/**
 * Draws maze with solution using specified formula in doxygen
 */
PNG* SquareMaze::drawCreativeMazeWithSolution()
{
  PNG *ret = drawCreativeMaze();
  vector<int> path = solveMaze();

  int currx = 5;
  int curry = 5;

  int counter;

  for (unsigned i = 0; i < path.size(); i++) {
    // CHANGE THIS TO COLOR OF SOLUTION
    HSLAPixel red ( rand() % 360 , 1.0 , 0.27 , 1);
    counter = 0;

    if (path[i] == 0) {
      while (counter < 10) {
        ret->getPixel(currx + counter, curry) = red;
        counter++;
      }

      currx += counter;
    }

    else if (path[i] == 1) {
      while (counter < 10) {
        ret->getPixel(currx, curry + counter) = red;
        counter++;
      }

      curry += counter;
    }

    else if (path[i] == 2) {
      while (counter < 10) {
        ret->getPixel(currx - counter, curry) = red;
        counter++;
      }

      currx -= counter;
    }

    else if (path[i] == 3) {
      while (counter < 10) {
        ret->getPixel(currx, curry - counter) = red;
        counter++;
      }

      curry -= counter;
    }
  }

  dest.down = false;
  maze[dest.x][dest.y].down = false;

  for(int k = 1; k <= 9; k++){
    ret->getPixel(dest.x * 10 + k, (dest.y + 1) * 10).l = 1.0;
  }

  return ret;
}


int SquareMaze::dist( int i, int j, int w, int h) const{
  double s = pow((w / 2 - i),2) + pow((h / 2 - j), 2);
  s = sqrt(s);
  double max = sqrt(pow(w / 2, 2) + pow(h / 2, 2));
  return (int) (360 * (s / max));
}
