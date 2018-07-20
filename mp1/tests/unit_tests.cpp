#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../mp1.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

using namespace cs225;

// default constructor
TEST_CASE("HSLAPixel's default constructor creates a white pixel", "[weight=1]") {
  HSLAPixel pixel;
  REQUIRE( pixel.l == 1 );
}

TEST_CASE("HSLAPixel's default constructor creates an opaque pixel", "[weight=1]") {
  HSLAPixel pixel;
  REQUIRE( pixel.a == 1 );
}


// 3-param constructor
TEST_CASE("HSLAPixel's HSL constructor creates a pixel with provided HSL values", "[weight=1]") {
  HSLAPixel pixel(260, 0.8, 0.7);
  REQUIRE( pixel.h == 260 );
  REQUIRE( pixel.s == 0.8 );
  REQUIRE( pixel.l == 0.7 );
}

TEST_CASE("HSLAPixel's HSL constructor creates an opaque pixel", "[weight=1]") {
  HSLAPixel pixel(260, 0.8, 0.7);
  REQUIRE( pixel.a == 1 );
}


// 4-param constructor
TEST_CASE("HSLAPixel's HSLA constructor creates a pixel with provided HSLA values", "[weight=1]") {
  HSLAPixel pixel(260, 0.8, 0.7, 0.4);
  REQUIRE( pixel.h == 260 );
  REQUIRE( pixel.s == 0.8 );
  REQUIRE( pixel.l == 0.7 );
  REQUIRE( pixel.a == 0.4 );
}


// Image tests
TEST_CASE("Rotate in_01.png", "[weight=1]") {
  rotate("tests/in_01.png", "tests/out.png");
  
  PNG expected, actual;
  expected.readFromFile("tests/out_01.png");
  actual.readFromFile("tests/out.png");

  REQUIRE(expected == actual);
}

TEST_CASE("Rotate in_02.png", "[weight=1]") {
  rotate("tests/in_02.png", "tests/out.png");
  
  PNG expected, actual;
  expected.readFromFile("tests/out_02.png");
  actual.readFromFile("tests/out.png");

  REQUIRE(expected == actual);
}

TEST_CASE("Rotate in_03.png", "[weight=1]") {
  rotate("tests/in_03.png", "tests/out.png");
  
  PNG expected, actual;
  expected.readFromFile("tests/out_03.png");
  actual.readFromFile("tests/out.png");

  REQUIRE(expected == actual);
}
