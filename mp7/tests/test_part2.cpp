
/**
#include "../cs225/catch/catch.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "../cs225/PNG.h"
#include "../dsets.h"
#include "../maze.h"
#include "mazereader.h"

using namespace cs225;
using namespace std;

void assert_maze_acyclic(SquareMaze & maze, int width, int height);
void assert_maze_connected(SquareMaze & maze, int width, int height);
void assert_maze_tree(SquareMaze & maze, int width, int height);
void copyMaze(const MazeReader & source, SquareMaze * dest);
void advancePosition(int * x, int * y, int dir);
PNG read_solution(const string & filename, int width, int height);
PNG read_unsolved(const string & filename, int width, int height);
#define READ_SOLUTION_PNG(func, width, height)  \
	read_solution(string("tests/soln_") + func + string(".png"), width, height)
#define READ_UNSOLVED_PNG(func, width, height)  \
	read_unsolved(string("tests/soln_") + func + string(".png"), width, height)
#define READ_SOLUTION_MAZE(func, width, height)  \
	MazeReader(READ_SOLUTION_PNG(func, width, height))
#define READ_UNSOLVED_MAZE(func, widht, height)  \
	MazeReader(READ_UNSOLVED_PNG(func, width, height))

void recDFS(SquareMaze & maze, vector<vector<uint8_t> > * visited, int x, int y, int width, int height, int * calls)
{
    stack< pair<int, int> > s;
    s.push(make_pair(x, y));

    while (!s.empty()) {
        x = s.top().first;
        y = s.top().second;
        s.pop();
        (*calls)++;
        if ((*visited)[x][y] != 0)
            continue;
        (*visited)[x][y] = 1;

        if (x < width-1 && maze.canTravel(x, y, 0))
            s.push(make_pair(x+1, y));
        if (y < height-1 && maze.canTravel(x, y, 1))
            s.push(make_pair(x, y+1));
        if (x > 0 && maze.canTravel(x, y, 2))
            s.push(make_pair(x-1, y));
        if (y > 0 && maze.canTravel(x, y, 3))
            s.push(make_pair(x, y-1));
    }
}

pair<int, int> assert_maze_helper(SquareMaze & maze, int width, int height)
{
	vector<vector<uint8_t> > visited;
	for (int i = 0; i < width; i++)
		visited.push_back(vector<uint8_t>(height));

	int components = 0;
	int calls = 0;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (visited[i][j] == 0) {
				recDFS(maze, &visited, i, j, width, height, &calls);
				components++;
			}
		}
	}

	return make_pair(components, calls);
}

void assert_maze_acyclic(SquareMaze & maze, int width, int height)
{
	pair<int, int> checks = assert_maze_helper(maze, width, height);
	int components = checks.first;
	int calls = checks.second;
	if (calls + components != width * height * 2)
		FAIL("Maze has a cycle");
}


void assert_maze_connected(SquareMaze & maze, int width, int height)
{
	pair<int, int> checks = assert_maze_helper(maze, width, height);
	int components = checks.first;
	int calls = checks.second;
	if (components != 1)
		FAIL("Maze is not connected");
}

void assert_maze_tree(SquareMaze & maze, int width, int height)
{
	pair<int, int> checks = assert_maze_helper(maze, width, height);
	int components = checks.first;
	int calls = checks.second;
	if (calls + components != width * height * 2)
		FAIL("Maze has a cycle");
	if (components != 1)
		FAIL("Maze is not connected");
}

PNG read_solution(const string & filename, int width, int height)
{
	  PNG output;
	  output.readFromFile(filename);
	  return output;
}

PNG read_unsolved(const string & filename, int width, int height)
{
	  PNG output;
	  output.readFromFile(filename);
	  return output;
}

void copyMaze(const MazeReader & source, SquareMaze * dest)
{
	dest->makeMaze(source.getWidth(), source.getHeight());
	for (int x = 0; x < source.getWidth(); x++)
	{
		for (int y = 0; y < source.getHeight(); y++)
		{
			if (x < source.getWidth() - 1)
				dest->setWall(x, y, 0, source.isWall(x, y, MazeReader::RIGHTWALL));
			if (y < source.getHeight() - 1)
				dest->setWall(x, y, 1, source.isWall(x, y, MazeReader::DOWNWALL));
		}
	}
}

void advancePosition(int * x, int * y, int dir)
{
	 if (dir == MazeReader::RIGHT)
		(*x)++;
	 else if (dir == MazeReader::DOWN)
		(*y)++;
	 else if (dir == MazeReader::LEFT)
		(*x)--;
	 else if (dir == MazeReader::UP)
		(*y)--;
}



//part2
TEST_CASE("testMakeSmallMaze", "[weight=10][part2]")
{
	SquareMaze maze;
	maze.makeMaze(2, 2);
	assert_maze_tree(maze, 2, 2);
}

TEST_CASE("testMakeMazeConnected", "[weight=10][part2]")
{
	SquareMaze maze;
	maze.makeMaze(15, 15);
	assert_maze_connected(maze, 15, 15);
}

TEST_CASE("testMakeMazeAcyclic", "[weight=10][part2]")
{
	SquareMaze maze;
	maze.makeMaze(15, 15);
	assert_maze_acyclic(maze, 15, 15);
}

TEST_CASE("testMakeMazeTree1000", "[weight=10][part2]")
{
	SquareMaze maze;
	maze.makeMaze(1000, 1000);
	assert_maze_tree(maze, 1000, 1000);
}

//THIS TEST_CASE NEEDS MODIFICATION
TEST_CASE("testMakeMazeRandom", "[weight=10][part2]")
{
	SquareMaze maze1;
	maze1.makeMaze(50, 50);
	PNG *p = maze1.drawMaze();
	//sleep(2);
	SquareMaze maze2;
	maze2.makeMaze(50, 50);
	p = maze2.drawMaze();
  bool same = true;

	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			if (maze1.canTravel(x, y, 0) != maze2.canTravel(x, y, 0)){
        same = false;
				break;
      }
			if (maze1.canTravel(x, y, 1) != maze2.canTravel(x, y, 1)){
        same = false;
				break;
      }
		}
	}
	if(same == false){
		SUCCEED();
	}
	else
		FAIL("Generated the same 50x50 maze twice");
}

TEST_CASE("testSolveMazeValidPath", "[weight=10][part2]")
{
	SquareMaze maze;
	MazeReader soln = READ_SOLUTION_MAZE("testSolveMazeValidPath", 15, 15);
	copyMaze(soln, &maze);
	vector<int> solution = maze.solveMaze();

	if (solution.empty())
		FAIL("No solution was generated");

	int x = 0;
	int y = 0;
	for (size_t i = 0; i < solution.size(); i++)
	{
		if (soln.isWallInDir(x, y, solution[i]))
			FAIL("Solution passes through walls");
		advancePosition(&x, &y, solution[i]);
	}
}

TEST_CASE("testSolutionBottomRow", "[weight=10][part2]")
{
	SquareMaze maze;
	MazeReader soln = READ_SOLUTION_MAZE("testSolutionBottomRow",15, 15);
	copyMaze(soln, &maze);
	vector<int> solution = maze.solveMaze();

	int x = 0;
	int y = 0;
	for (size_t i = 0; i < solution.size(); i++)
		advancePosition(&x, &y, solution[i]);

	if (y != soln.getDestinationY())
		FAIL("Didn't end up at the bottom row");
}

TEST_CASE("testSolutionCorrectSquare", "[weight=10][part2]")
{
	SquareMaze maze;
	MazeReader soln = READ_SOLUTION_MAZE("testSolutionCorrectSquare",15, 15);
	copyMaze(soln, &maze);
	vector<int> solution = maze.solveMaze();

	int x = 0;
	int y = 0;
	for (size_t i = 0; i < solution.size(); i++)
		advancePosition(&x, &y, solution[i]);

	if (y != soln.getDestinationY())
		FAIL("Didn't end up at the bottom row");
	if (x != soln.getDestinationX())
		FAIL("Didn't end up at the correct bottom-row cell");
}


// The MazeReader object must be passed in because READ_SOLUTION uses
// the function name to name the file
void helpSolveMaze(const MazeReader & soln)
{
	SquareMaze maze;
	copyMaze(soln, &maze);
	vector<int> solution = maze.solveMaze();

	cout << "first 10 steps in solution:" << endl;
	for (size_t i = 0; i < solution.size() && i < soln.getSolutionSize() && i < 10; i++)
		cout << "step " << i << ": actual=" << solution[i] << ", expected=" << soln.getSolutionAt(i) << endl;

	REQUIRE(soln.getSolutionSize() == solution.size());

	for (size_t i = 0; i < solution.size(); i++)
		if (solution[i] != soln.getSolutionAt(i))
			FAIL("Solution is incorrect");
}

TEST_CASE("testSolveMazeSmall", "[weight=10][part2]") {
	 helpSolveMaze(READ_SOLUTION_MAZE("testSolveMazeSmall",700, 700));
}

TEST_CASE("testSolveMazeLarge", "[weight=10][part2]") {
	helpSolveMaze(READ_SOLUTION_MAZE("testSolveMazeLarge", 700, 700));
}


TEST_CASE("testDrawMazeSmall", "[weight=10][part2]")
{
	PNG solnImage = READ_UNSOLVED_PNG("testDrawMazeSmall", 2, 2);
	MazeReader soln(solnImage);
	SquareMaze maze;
	copyMaze(soln, &maze);
	PNG * actualOutput = maze.drawMaze();
	actualOutput->writeToFile("testDrawMazeSmall"+ string(".png"));
	REQUIRE(*actualOutput == solnImage);
}

TEST_CASE("testDrawMazeMed", "[weight=10][part2]")
{
	PNG solnImage = READ_UNSOLVED_PNG("testDrawMazeMed",50, 50);
	MazeReader soln(solnImage);
	SquareMaze maze;
	copyMaze(soln, &maze);
	PNG * actualOutput = maze.drawMaze();
	REQUIRE(*actualOutput == solnImage);
}

TEST_CASE("testDrawMazeLarge", "[weight=10][part2]")
{
	PNG solnImage = READ_UNSOLVED_PNG("testDrawMazeLarge",500, 500);
	MazeReader soln(solnImage);
	SquareMaze maze;
	copyMaze(soln, &maze);
	PNG * actualOutput = maze.drawMaze();
	actualOutput->writeToFile("testDrawMazeLarge" + string(".png"));
	REQUIRE(*actualOutput == solnImage);
}

TEST_CASE("testDrawSolutionMed", "[weight=10][part2]")
{
	PNG solnImage = READ_SOLUTION_PNG("testDrawSolutionMed",50, 50);
	MazeReader soln(solnImage);
	SquareMaze maze;
	copyMaze(soln, &maze);
	maze.solveMaze();
	PNG * actualOutput = maze.drawMazeWithSolution();
	actualOutput->writeToFile("testDrawSolutionMed" + string(".png"));
	REQUIRE(*actualOutput == solnImage);
}

TEST_CASE("testDrawSolutionLarge", "[weight=10][part2]")
{
	PNG solnImage = READ_SOLUTION_PNG("testDrawSolutionLarge",500, 500);
	MazeReader soln(solnImage);
	SquareMaze maze;
	copyMaze(soln, &maze);
	maze.solveMaze();
	PNG * actualOutput = maze.drawMazeWithSolution();
	actualOutput->writeToFile("testDrawSolutionLarge"+ string(".png"));
	REQUIRE(*actualOutput == solnImage);
}
 */

