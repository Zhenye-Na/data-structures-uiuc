/*
#include "../cs225/catch/catch.hpp"
#include "../Image.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"
#include "../StickerSheet.h"

using namespace cs225;

TEST_CASE("A basic StickerSheet works", "[weight=5][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  Image expected;
  expected.readFromFile("tests/expected.png");

  REQUIRE( sheet.render() == expected );
}


TEST_CASE("StickerSheet::changeMaxStickers() does not discard stickers when resized larger", "[weight=1][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  sheet.changeMaxStickers(7);

  Image expected;
  expected.readFromFile("tests/expected.png");

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::changeMaxStickers() does not discard original stickers when resized smaller", "[weight=1][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  sheet.changeMaxStickers(3);

  Image expected;
  expected.readFromFile("tests/expected.png");

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::changeMaxStickers() can increase the number of stickers on an image", "[weight=1][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 1);
  sheet.addSticker(i, 20, 200);

  sheet.changeMaxStickers(2);
  sheet.addSticker(i, 40, 200);

  Image expected;
  expected.readFromFile("tests/expected-2.png");

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::changeMaxStickers() discards stickers beyond the end of a smaller StickerSheet", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40, 200);
  sheet.addSticker(i, 60, 200);
  sheet.changeMaxStickers(1);

  REQUIRE( sheet.render() == expected );
}







//
// test removeSticker
//
TEST_CASE("StickerSheet::removeSticker() can remove the last sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 50, 200);
  sheet.removeSticker(1);

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::removeSticker() can remove the first sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);
  sheet.addSticker(i, 20, 200);
  sheet.removeSticker(0);

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::removeSticker() can remove all stickers", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 80, 200);
  sheet.removeSticker(2);
  sheet.removeSticker(1);
  sheet.removeSticker(0);

  REQUIRE( sheet.render() == alma );
}



//
// test that getSticker works
//
TEST_CASE("StickerSheet::getSticker() returns the sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);

  REQUIRE( *(sheet.getSticker(0)) == i );
}

TEST_CASE("StickerSheet::getSticker() returns NULL for a non-existant sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);

  REQUIRE( sheet.getSticker(1) == NULL );
}

TEST_CASE("StickerSheet::getSticker() returns NULL for a removed sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);
  sheet.removeSticker(0);

  REQUIRE( sheet.getSticker(0) == NULL );
}


//
// translate
//
TEST_CASE("StickerSheet::translate() translates a sticker's location", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 0, 0);
  sheet.translate(0, 20, 200);

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::translate() returns false for a non-existant sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  REQUIRE( sheet.translate(3, 20, 200) == false );
}


//
// render
//
TEST_CASE("A complex StickerSheet is correct", "[weight=5][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected-3.png");

  StickerSheet sheet(alma, 100);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40, 200);
  sheet.addSticker(i, 60, 200);
  sheet.addSticker(i, 80, 200);
  sheet.addSticker(i, 100, 200);
  sheet.addSticker(i, 120, 200);
  sheet.addSticker(i, 140, 200);
  sheet.removeSticker(3);
  sheet.translate(0, 0, 0);

  REQUIRE( sheet.render() == expected );
}


//
// copy ctor
//
TEST_CASE("StickerSheet's copy constructor makes an independent copy", "[weight=2][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");
  Image expected2; expected2.readFromFile("tests/expected-2.png");

  StickerSheet s1(alma, 5);
  s1.addSticker(i, 20, 200);
  s1.addSticker(i, 40, 200);

  StickerSheet s2(s1);
  s2.removeSticker(1);

  REQUIRE( s1.render() == expected2 );
  REQUIRE( s2.render() == expected );
}

TEST_CASE("StickerSheet's assignment operator makes an independent copy", "[weight=2][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");
  Image expected2; expected2.readFromFile("tests/expected-2.png");

  StickerSheet s1(alma, 5);
  s1.addSticker(i, 20, 200);
  s1.addSticker(i, 40, 200);

  StickerSheet s2(alma, 5);
  s2 = s1;
  s2.removeSticker(1);

  REQUIRE( s1.render() == expected2 );
  REQUIRE( s2.render() == expected );
}
*/
