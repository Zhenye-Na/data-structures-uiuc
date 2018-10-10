#include "../cs225/catch/catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <locale>

#include "../kdtree.h"
#include "../point.h"

// https://stackoverflow.com/a/217605
// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// compare the two streams for equality
bool tree_equals_output(stringstream & s, string filename)
{
    ifstream file(filename);
    string soln_s;
    string out_s;

    while(getline(file, soln_s))
    {
        if(!getline(s, out_s))
            return false;

        rtrim(soln_s);
        rtrim(out_s);

        if(out_s != soln_s)
            return false;
    }
    if(getline(s, soln_s))
        return false;

    return true;
}

void compareBinaryFiles( string yourFile, string ourFile ) 
{
    ifstream ourBinary( ourFile, ios::binary );
    stringstream ours;
    ours << ourBinary.rdbuf();

    if(!tree_equals_output(ours, yourFile))
        FAIL( "Your output in \"" + yourFile + "\" does not match our output in \"" + ourFile + "\"");
}

TEST_CASE("KDTree::testSmallerDimVal Tests", "[weight=1][part=1]") {
  vector<Point<3>> pts;
  KDTree<3> tree(pts);
  Point<3> a(1, 2, 3);
  Point<3> b(3, 2, 1);

  REQUIRE( tree.smallerDimVal(a, b, 0) == true );
  REQUIRE( tree.smallerDimVal(a, b, 2) == false );
  REQUIRE( tree.smallerDimVal(a, b, 1) == true );   // based on operator<
}

TEST_CASE("KDTree::shouldReplace Tests", "[weight=1][part=1]") {
  vector<Point<3>> pts;
  KDTree<3> tree(pts);

  Point<3> target(1, 3, 5);
  Point<3> currentBest1(1, 3, 2);
  Point<3> possibleBest1(2, 4, 4);
  Point<3> currentBest2(1, 3, 6);
  Point<3> possibleBest2(2, 4, 4);
  Point<3> currentBest3(0, 2, 4);
  Point<3> possibleBest3(2, 4, 6);

  REQUIRE( tree.shouldReplace(target, currentBest1, possibleBest1) == true );
  REQUIRE( tree.shouldReplace(target, currentBest2, possibleBest2) == false );
  REQUIRE( tree.shouldReplace(target, currentBest3, possibleBest3) == false );  // operator<
}


//
// Simple Constructor
//
template <int K>
void _test_linear_constructor(int size) {
  vector<Point<K>> points;
  points.reserve(size);
  for (int i = 0; i < size; i++) {
      Point<K> p;
      for (int j = 0; j < K; j++)
          p[j] = i;
      points.push_back(p);
  }

  KDTree<K> tree(points);

  std::string fname = "test_result_kdtree_"+to_string(size)+".kd";

  ofstream outputFile(fname, ofstream::out);
  tree.printTree(outputFile, colored_out::DISABLE, -1);
  outputFile.close();

  compareBinaryFiles(fname, "tests/expected_kdtree_"+to_string(size)+".kd" );
}

TEST_CASE("KDTree constructor, 1D (Dim=1)", "[weight=1][part=1]") {
  _test_linear_constructor<1>(10);
}

TEST_CASE("KDTree constructor, 3D (Dim = 3)", "[weight=1][part=1]") {
  _test_linear_constructor<3>(31);
  }


//
// Simple Nearest Neighbor
//
template <int K>
void _test_linear_nearestNeighbor(int size) {
  vector<Point<K>> points;
  points.reserve(size);
  for (int i = 0; i < size; i++) {
      Point<K> p;
      for (int j = 0; j < K; j++)
          p[j] = i;
      points.push_back(p);
  }

  KDTree<K> tree(points);
  for (int i = 0; i < size; i++) {
    REQUIRE ( tree.findNearestNeighbor(points[i]) == points[i] );
  }
}

TEST_CASE("KDTree::findNearestNeighbor, exact match, 1D (Dim=1)", "[weight=1][part=1]") {
  _test_linear_nearestNeighbor<1>(10);
}

TEST_CASE("KDTree::findNearestNeighbor, exact match, 3D (Dim=3)", "[weight=1][part=1]") {
  _test_linear_nearestNeighbor<3>(31);
  }


/*****************************************
*                    8                   *
*     X              7     X             *
*                    6                   *
*                    5                   *
*                    4                   *
*                    3                   *
*                    2             X     *
*       O            1                   *
* 9876543210987 X 32101234567890123456789*
*       X            1                   *
*                    2                   *
*                    3             X     *
*                    4                   *
*                    5                   *
*                    6                   *
*                    7                   *
*                    8                   *
*****************************************/
// Looking for O, Xs are points
TEST_CASE("KDTree::findNearestNeighbor (2D), returns correct result", "[weight=1][part=1]") {
  double coords[6][2] = {
    {-15, 7}, {6, 7}, {-13, -1},
    {-5, 0}, {14, -3}, {14, 2}
  };
  double targetCoords[2] = {-13, 1};
  double expectedCoords[2] = {-13, -1};

  vector<Point<2>> points;
  for (int i = 0; i < 6; ++i)
      points.push_back(Point<2>(coords[i]));
  Point<2> target(targetCoords);
  Point<2> expected(expectedCoords);

  KDTree<2> tree(points);
  REQUIRE( tree.findNearestNeighbor(target) == expected );
}


/*
 * Extend Point to create a MinePoint, having an additional field for if the
 * current point is a mine.  If a mine is visited, the test case FAILs.
 */
template <int Dim>
class MineActionFAIL : public Point<Dim>::MineAction {
  public:
    void onMine(const Point<Dim> & point) const {
        // only fail if trigger is set;
        // gets set after construction and before findNN call
        if (trigger)
            FAIL("The point " << point << " should not be visited during this query.");
    }

    bool trigger = false;
};


/***********************
*    X      8          *
*           7          *
*       X   6          *
*     O  X      5      *
*      N    X   4      *
*               3      *
*           2          *
*           1          *
* 098765432101 X 567890*
*           1          *
*           2          *
*           3     M    *
*           4          *
*           5   X      *
*           6      M   *
*           7 M        *
***********************/
// M: mine
// O: search target
// N: nearest neighbor
// X: non-mine elements
TEST_CASE("KDTree::findNearestNeighbor (2D), testing correct path", "[weight=1][part=1]") {
    double coords[10][2] = {
      {-8, 7}, {-6, 4}, {-5, 6}, {-3, 5}, {0, 7},
      //                ^NN
      {2, -7}, {3, 0},  {5, -4}, {6, -3}, {7, -6}
      //^M     ^M       ^M       ^M       ^M
    };

    bool isMine[10] = {false, false, false, false, false, true, true, true, true, true};
    double targetCoords[2] = {-7, 5};
    double expectedCoords[2] = {-6, 4};

    // Using MinePoint to FAIL for bad paths
    vector<Point<2>> points;
    MineActionFAIL<2> action;
    for (int i = 0; i < 10; ++i)
        points.push_back(Point<2>(coords[i], isMine[i], &action));
    Point<2> target(targetCoords);
    Point<2> expected(expectedCoords);

    KDTree<2> tree(points);

    stringstream s;
    tree.printTree(s, colored_out::enable_t::DISABLE);
    INFO(s.str());

    action.trigger = true;

    REQUIRE( tree.findNearestNeighbor(target) == expected );
}


/*

*/
TEST_CASE("KDTree::findNearestNeighbor (2D), testing correct path with fence jumping", "[weight=1][part=1]") {
  double coords[20][2] = {{84, 44},  // mine
                          {74, 0},   // mine
                          {54, 62},  // mine
                          {59, 0},   // mine
                          {34, 15},  // mine
                          {42, 63},
                          {96, 56},  // mine
                          {44, 79},
                          {44, 43},
                          {28, 10},  // mine
                          {60, 30},  // mine
                          {88, 72},  // mine
                          {75, 68},  // mine
                          {43, 65},
                          {48, 0},   // mine
                          {14, 15},  // mine
                          {49, 83},
                          {51, 35},
                          {95, 50},  // mine
                          {82, 20}}; // mine
  bool isMine[20] = {1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1};
  double targetCoords[2] = {45, 59};
  double expectedCoords[2] = {42, 63};


  vector<Point<2>> points;
  MineActionFAIL<2> action;
  for (int i = 0; i < 20; ++i)
      points.push_back(Point<2>(coords[i], isMine[i], &action));
  Point<2> target(targetCoords);
  Point<2> expected(expectedCoords);

  KDTree<2> tree(points);

  stringstream s;
  tree.printTree(s, colored_out::enable_t::DISABLE);
  INFO(s.str());

  action.trigger = true;

  REQUIRE(tree.findNearestNeighbor(target) == expected);
}


TEST_CASE("KDTree::findNearestNeighbor (3D), testing tie-breaking", "[weight=1][part=1]") {
  double coords[14][3] = {{0, 0, 100},   // mine
                          {0, 100, 100}, // mine
                          {0, 50, 50},   // mine
                          {0, 0, 50},    // mine
                          {100, 0, 100}, // mine
                          {100, 100, 0},
                          {0, 0, 0},
                          {0, 50, 0},    // mine
                          {50, 0, 0},    // mine
                          {50, 0, 50},   // mine
                          {100, 0, 0},   // mine
                          {50, 50, 0},
                          {0, 100, 0},   // mine
                          {50, 50, 50}};
  bool isMine[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  double targetCoords[3] = {50, 100, 0};
  double expectedCoords[3] = {0, 100, 0};
  double targetCoords2[3] = {14, 17, 20};
  double expectedCoords2[3] = {0, 0, 0};

  vector<Point<3>> points;
  MineActionFAIL<3> action;
  for (int i = 0; i < 14; ++i)
      points.push_back(Point<3>(coords[i], isMine[i], &action));
  Point<3> target(targetCoords);
  Point<3> expected(expectedCoords);
  Point<3> target2(targetCoords2);
  Point<3> expected2(expectedCoords2);

  KDTree<3> tree(points);

  stringstream s;
  tree.printTree(s, colored_out::enable_t::DISABLE);
  INFO(s.str());

  action.trigger = true;

  REQUIRE( tree.findNearestNeighbor(target) == expected );
  REQUIRE( tree.findNearestNeighbor(target2) == expected2 );
}


TEST_CASE("KDTree::findNearestNeighbor (3D), testing that left recursion does not include the root", "[weight=1][part=1]") {
  double coords[10][3] = {
    {5, 3, 1}, {3, 1, 10}, {2, 0, 8}, {4, 3, 0}, {0, 2, 9},
    {10, 10, 10}, {11, 11, 11}, {12, 12, 12}, {13, 13, 13}, {14, 14, 14}
  };
  double targetCoords[3] = {1, 1, 9};
  double expectedCoords[3] = {0, 2, 9};

  vector<Point<3>> points;
  for (int i = 0; i < 10; ++i)
      points.push_back(Point<3>(coords[i]));
  Point<3> target(targetCoords);
  Point<3> expected(expectedCoords);

  KDTree<3> tree(points);
  REQUIRE( tree.findNearestNeighbor(target) == expected );
}
