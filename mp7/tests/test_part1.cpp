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


TEST_CASE("addElements1", "[weight=10][part1]")
{
	DisjointSets disjSets;
	disjSets.addelements(5);
	REQUIRE(3 == disjSets.find(3));
}

TEST_CASE("addElements2", "[weight=10][part1]")
{
	DisjointSets disjSets;
	disjSets.addelements(5);
	REQUIRE(0 == disjSets.find(0));
	disjSets.addelements(5);
	REQUIRE(9 == disjSets.find(9));
}

TEST_CASE("testFindAndSetUnion1", "[weight=10][part1]")
{
	DisjointSets disjSets;
	disjSets.addelements(4);
	disjSets.setunion(1, 2);
	REQUIRE(disjSets.find(2) == disjSets.find(1));
}

TEST_CASE("testFindAndSetUnion2", "[weight=10][part1]")
{
	DisjointSets disjSets;
	disjSets.addelements(10);

	disjSets.setunion(4, 8);
	disjSets.setunion(1, 3);
	disjSets.setunion(1, 5);
	disjSets.setunion(8, 3);
	disjSets.setunion(6, 7);
	disjSets.setunion(2, 8);
	disjSets.setunion(7, 1);

	int root = disjSets.find(1);
	for (int i = 2; i <= 8; i++)
		REQUIRE(root == disjSets.find(i));
	REQUIRE(disjSets.find(0) != disjSets.find(9));
}

TEST_CASE("testFindAndSetUnion3", "[weight=10][part1]")
{
	DisjointSets disjSets;
	disjSets.addelements(8);

	disjSets.setunion(1, 2);
	disjSets.setunion(1, 3);
	disjSets.setunion(4, 5);
	disjSets.setunion(4, 6);
	disjSets.setunion(3, 6);

	REQUIRE(disjSets.find(4) == disjSets.find(1));
	REQUIRE(disjSets.find(0) != disjSets.find(4));
}
