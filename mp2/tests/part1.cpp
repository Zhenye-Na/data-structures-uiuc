#include "../cs225/catch/catch.hpp"
#include "../Image.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

using namespace cs225;

Image createRainbowImage() {
  Image png;
  png.resize(360, 100);

  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      pixel.h = x;
      pixel.s = y / 100.0;
      pixel.l = y / 100.0;
    }
  }
  return png;
}


//
// lighten, darken
//
TEST_CASE("Image lighten() lightens pixels by 0.1", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.lighten();

  REQUIRE( img.getPixel(10, 10).l + 0.1 == result.getPixel(10, 10).l );
}

TEST_CASE("Image lighten() does not lighten a pixel above 1.0", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.lighten();

  REQUIRE( 1.0 == result.getPixel(10, 95).l );
}

TEST_CASE("Image darken(0.2) darkens pixels by 0.2", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.darken(0.2);

  REQUIRE( img.getPixel(50, 50).l - 0.2 == result.getPixel(50, 50).l );
}

TEST_CASE("Image darken(0.2) does not darken a pixel below 0.0", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.darken(0.2);

  REQUIRE( 0 == result.getPixel(5, 5).l );
}


//
// saturate, desaturate
//
TEST_CASE("Image saturate() saturates a pixels by 0.1", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.saturate();

  REQUIRE( img.getPixel(10, 10).s + 0.1 == result.getPixel(10, 10).s );
}


//
// rotateColor
//
TEST_CASE("Image rotateColor(double) rotates the color", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.rotateColor(90);

  REQUIRE( img.getPixel(90, 90).h + 90 == result.getPixel(90, 90).h );
}

TEST_CASE("Image rotateColor(double) keeps the hue in the range [0, 360]", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.rotateColor(90);
  REQUIRE( result.getPixel(340, 90).h == 70 );

  result.rotateColor(-180);
  REQUIRE( result.getPixel(10, 90).h == 280 );
}


//
// scale
//
TEST_CASE("Image scale(2.0) results in the correct width/height", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.scale(2.0);

  REQUIRE( img.height() * 2 == result.height() );
}

TEST_CASE("Image scale(0.5) results in the correct width/height", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.scale(0.5);

  REQUIRE( img.height() * 0.5 == result.height() );
}

TEST_CASE("Image scale(2) scales pixel data in a reasonable way", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.scale(2);

  REQUIRE( result.getPixel(100, 100).h > 40 );
  REQUIRE( result.getPixel(100, 100).h < 60 );
}

TEST_CASE("Image scale(0.5) scales pixel data in a reasonable way", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.scale(0.5);

  REQUIRE( result.getPixel(100, 20).h > 180 );
  REQUIRE( result.getPixel(100, 20).h < 220 );
}
