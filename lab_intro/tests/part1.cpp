#include "catch.hpp"

#include "../lab_intro.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

// HSLAPixel default constructor
TEST_CASE("HSLAPixel's default constructor creates a white pixel", "[weight=1]") {
  HSLAPixel pixel;
  REQUIRE( pixel.l == 1 );
}

TEST_CASE("HSLAPixel's default constructor creates an opaque pixel", "[weight=1]") {
  HSLAPixel pixel;
  REQUIRE( pixel.a == 1 );
}


// HSLAPixel 3-param constructor
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


// HSLAPixel 4-param constructor
TEST_CASE("HSLAPixel's HSLA constructor creates a pixel with provided HSLA values", "[weight=1]") {
  HSLAPixel pixel(260, 0.8, 0.7, 0.4);
  REQUIRE( pixel.h == 260 );
  REQUIRE( pixel.s == 0.8 );
  REQUIRE( pixel.l == 0.7 );
  REQUIRE( pixel.a == 0.4 );
}