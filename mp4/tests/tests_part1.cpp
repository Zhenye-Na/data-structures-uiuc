#include "catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

#include "../imageTraversal/BFS.h"
#include "../imageTraversal/DFS.h"

using namespace cs225;


/**
 * Returns a 4x4 image with a white center and black border:
 * 
 *     X X X X
 *     X - - X       X: black
 *     X - - X       -: white
 *     X X X X
 * 
 * The black/X (h=180, s=1, l=0) is as different from
 * white/- (h=0, s=0, l=1) as possible.
**/
PNG getTestPNG() {
  PNG png(4, 4);
  HSLAPixel blackPixel(180, 1, 0);
  
  for (unsigned i = 0; i < 4; i++) {    
    png.getPixel(i, 0) = blackPixel;
    png.getPixel(0, i) = blackPixel;
    png.getPixel(i, 3) = blackPixel;
    png.getPixel(3, i) = blackPixel;
  }
    
  return png;
}


TEST_CASE("DFS iterator starts at the start point", "[weight=1][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(1, 1);
  
  DFS dfs(png, startPoint, 0.2);
  REQUIRE( *(dfs.begin()) == startPoint );
}

TEST_CASE("DFS visits the correct pixel first", "[weight=1][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(1, 1);
  
  DFS dfs(png, startPoint, 0.2);
  ImageTraversal::Iterator it = dfs.begin();
  ++it;
  REQUIRE( *it == Point(1, 2) );
}


TEST_CASE("BFS iterator starts at the start point", "[weight=1][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(1, 1);
  
  BFS bfs(png, startPoint, 0.2);
  REQUIRE( *(bfs.begin()) == startPoint );
}

TEST_CASE("BFS visits the correct pixel first", "[weight=1][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(1, 1);
  
  BFS bfs(png, startPoint, 0.2);
  ImageTraversal::Iterator it = bfs.begin();
  ++it;
  REQUIRE( *it == Point(2, 1) );
}


TEST_CASE("DFS visits all points within a tolerance", "[weight=1][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(1, 1);
  
  DFS t(png, startPoint, 0.2);
  unsigned count = 0;
  for (const Point & p : t) {
    count++;
  }
  REQUIRE( count == 4 );
}

TEST_CASE("BFS visits all points within a tolerance", "[weight=1][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(1, 1);
  
  BFS t(png, startPoint, 0.2);
  unsigned count = 0;
  for (const Point & p : t) {
    count++;
  }
  REQUIRE( count == 4 );
}


TEST_CASE("DFS visits all points within a tolerance (includes pixels on image edge)", "[weight=1][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(0, 0);
  
  DFS t(png, startPoint, 0.2);
  unsigned count = 0;
  for (const Point & p : t) { count++; }

  REQUIRE( count == 12 );
}

TEST_CASE("BFS visits all points within a tolerance (includes pixels on image edge)", "[weight=1][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(0, 0);
  
  BFS t(png, startPoint, 0.2);
  unsigned count = 0;
  for (const Point & p : t) { count++; }

  REQUIRE( count == 12 );
}


TEST_CASE("DFS iterator visits all points in the correct order", "[weight=1][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(0, 0);
  
  DFS t(png, startPoint, 0.2);
  ImageTraversal::Iterator it = t.begin();

  REQUIRE( *it == Point(0, 0) ); ++it;
  REQUIRE( *it == Point(0, 1) ); ++it;
  REQUIRE( *it == Point(0, 2) ); ++it;
  REQUIRE( *it == Point(0, 3) ); ++it;
  REQUIRE( *it == Point(1, 3) ); ++it;
  REQUIRE( *it == Point(2, 3) ); ++it;  
  REQUIRE( *it == Point(3, 3) ); ++it;
  REQUIRE( *it == Point(3, 2) ); ++it;
  REQUIRE( *it == Point(3, 1) ); ++it;  
  REQUIRE( *it == Point(3, 0) ); ++it;
  REQUIRE( *it == Point(2, 0) ); ++it;
  REQUIRE( *it == Point(1, 0) ); ++it;  
}

TEST_CASE("BFS iterator visits all points in the correct order", "[weight=1][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(0, 0);
  
  BFS t(png, startPoint, 0.2);
  ImageTraversal::Iterator it = t.begin();

  REQUIRE( *it == Point(0, 0) ); ++it;

  REQUIRE( *it == Point(1, 0) ); ++it;  
  REQUIRE( *it == Point(0, 1) ); ++it;

  REQUIRE( *it == Point(2, 0) ); ++it;  
  REQUIRE( *it == Point(0, 2) ); ++it;

  REQUIRE( *it == Point(3, 0) ); ++it;
  REQUIRE( *it == Point(0, 3) ); ++it;

  REQUIRE( *it == Point(3, 1) ); ++it;
  REQUIRE( *it == Point(1, 3) ); ++it;
  
  REQUIRE( *it == Point(3, 2) ); ++it;
  REQUIRE( *it == Point(2, 3) ); ++it;

  REQUIRE( *it == Point(3, 3) ); ++it;
}
