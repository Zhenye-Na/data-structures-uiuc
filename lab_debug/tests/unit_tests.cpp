#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../sketchify.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

using namespace cs225;


bool fileExists(std::string fileName) {
  std::ifstream f(fileName.c_str());
  bool exists = f.good();
  f.close();

  return exists;
}


//
// Basic tests
//
TEST_CASE("Runs without a seg fault", "[weight=2]") {
	sketchify("tests/in_01.png", "tests/out.png");
}

TEST_CASE("Produces an output PNG file", "[weight=1]") {
  const std::string fileName = "tests/out_existanceTest.png";

  // Delete if tests/out_existanceTest exists... if so, delete it.
  if (fileExists(fileName)) { remove( fileName.c_str() ); }

  // Run program
  sketchify("tests/in_01.png", fileName);

  // Check for file existance
  REQUIRE( fileExists(fileName) == true );
  remove( fileName.c_str() );
}


//
// Similar output tests
//
TEST_CASE("Pixels that are part of the sketch are your favorite color", "[weight=2]") {
  sketchify("tests/in_01.png", "tests/out.png");

  PNG png;
  png.readFromFile("tests/out.png");

  PNG expected;
  expected.readFromFile("tests/out_01.png");

  for (unsigned x = 0; x < expected.width(); x++) {
    for (unsigned y = 0; y < expected.height(); y++) {
      if ( expected.getPixel(x, y).l != 1 ) {
        REQUIRE( png.getPixel(x, y).l != 1 );
      }
    }
  }
}

TEST_CASE("Pixels that are NOT part of the sketch are white", "[weight=1]") {
  sketchify("tests/in_01.png", "tests/out.png");

  PNG png;
  png.readFromFile("tests/out.png");

  PNG expected;
  expected.readFromFile("tests/out_01.png");

  for (unsigned x = 0; x < expected.width(); x++) {
    for (unsigned y = 0; y < expected.height(); y++) {
      if ( expected.getPixel(x, y).l == 1 ) {
        REQUIRE( png.getPixel(x, y).l == 1 );
      }
    }
  }
}


//
// Exact output tests
//
TEST_CASE("in_01.png produces a correct sketch", "[weight=2]") {
  sketchify("tests/in_01.png", "tests/out.png");

  PNG expected, png;
  expected.readFromFile("tests/out_01.png");
  png.readFromFile("tests/out.png");

  for (unsigned x = 0; x < expected.width(); x++) {
    for (unsigned y = 0; y < expected.height(); y++) {
      if (expected.getPixel(x, y).l == 1) {
        REQUIRE( png.getPixel(x, y).l == 1 );
      } else {
        REQUIRE( png.getPixel(x, y).l != 1 );
      }
    }
  }
}

TEST_CASE("in_02.png produces a correct sketch", "[weight=1]") {
  sketchify("tests/in_02.png", "tests/out.png");

  PNG expected, png;
  expected.readFromFile("tests/out_02.png");
  png.readFromFile("tests/out.png");

  for (unsigned x = 0; x < expected.width(); x++) {
    for (unsigned y = 0; y < expected.height(); y++) {
      if (expected.getPixel(x, y).l == 1) {
        REQUIRE( png.getPixel(x, y).l == 1 );
      } else {
        REQUIRE( png.getPixel(x, y).l != 1 );
      }
    }
  }
}

TEST_CASE("in_03.png produces a correct sketch", "[weight=1]") {
  sketchify("tests/in_03.png", "tests/out.png");

  PNG expected, png;
  expected.readFromFile("tests/out_03.png");
  png.readFromFile("tests/out.png");

  for (unsigned x = 0; x < expected.width(); x++) {
    for (unsigned y = 0; y < expected.height(); y++) {
      if (expected.getPixel(x, y).l == 1) {
        REQUIRE( png.getPixel(x, y).l == 1 );
      } else {
        REQUIRE( png.getPixel(x, y).l != 1 );
      }
    }
  }
}
