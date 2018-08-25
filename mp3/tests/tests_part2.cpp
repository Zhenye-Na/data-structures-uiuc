#include "../cs225/catch/catch.hpp"
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

#include "../list.h"

using namespace cs225;

TEST_CASE("List::split", "[weight=1][part=2]") {
  PNG in;         in.readFromFile("tests/split.png");
  PNG expected_1; expected_1.readFromFile("tests/expected-split_1.png");
  PNG expected_2; expected_2.readFromFile("tests/expected-split_2.png");
  PNG expected_3; expected_3.readFromFile("tests/expected-split_3.png");

  List<HSLAPixel> list1;
  for (unsigned i = 0; i < in.width(); i++)
      for (unsigned j = 0; j < in.height(); j++)
          list1.insertBack(in.getPixel(i, j));
  List<HSLAPixel> list2 = list1.split(400 * 240);
  List<HSLAPixel> list3 = list2.split(400 * 240);

  vector<HSLAPixel> im1vect(list1.begin(), list1.end());
  vector<HSLAPixel> im2vect(list2.begin(), list2.end());
  vector<HSLAPixel> im3vect(list3.begin(), list3.end());

  PNG out1(400, 240);
  unsigned x = 0;
  for (unsigned i = 0; i < im1vect.size(); i++) {
      unsigned y = i % 240;
      out1.getPixel(x, y) = im1vect[i];
      if (y == 239) { x++; }
  }
  out1.writeToFile("actual-split_1.png");
  INFO("Output image `out1` saved as actual-split_1.png");
  REQUIRE( out1 == expected_1 );


  PNG out2(400, 240);
  x = 0;
  for (size_t i = 0; i < im2vect.size(); i++) {
      int y = i % 240;
      out2.getPixel(x, y) = im2vect[i];
      if (y == 239)
          x++;
  }
  out2.writeToFile("actual-split_2.png");
  INFO("Output image `out2` saved as actual-split_2.png");
  REQUIRE( out2 == expected_2 );


  PNG out3(400, 240);
  x = 0;
  for (size_t i = 0; i < im3vect.size(); i++) {
      int y = i % 240;
      out3.getPixel(x, y) = im3vect[i];
      if (y == 239)
          x++;
  }
  out3.writeToFile("actual-split_3.png");
  INFO("Output image `out3` saved as actual-split_3.png");
  REQUIRE( out3 == expected_3 );
}


TEST_CASE("List::merge", "[weight=1][part=2]") {
  PNG im1;       im1.readFromFile("tests/merge1.png");
  PNG im2;       im2.readFromFile("tests/merge2.png");
  PNG expected;  expected.readFromFile("tests/expected-merge.png");

  PNG out(600, 400);

  vector<HSLAPixel> v1;
  for (unsigned i = 0; i < im1.width(); i++)
      for (unsigned j = 0; j < im1.height(); j++)
          v1.push_back(im1.getPixel(i, j));
  vector<HSLAPixel> v2;
  for (unsigned i = 0; i < im2.width(); i++)
      for (unsigned j = 0; j < im2.height(); j++)
          v2.push_back(im2.getPixel(i, j));
  List<HSLAPixel> l1(v1.begin(), v1.end());
  List<HSLAPixel> l2(v2.begin(), v2.end());
  l1.mergeWith(l2);
  vector<HSLAPixel> merged(l1.begin(), l1.end());
  unsigned x = 0;
  for (unsigned i = 0; i < merged.size(); i++) {
      int y = i % 400;
      out.getPixel(x, y) = merged[i];
      if (y == 399)
          x++;
  }

  out.writeToFile("actual-merge.png");
  INFO("Output image `out` saved as actual-merge.png");

  REQUIRE( out == expected );
}

TEST_CASE("List::sort #1", "[weight=1][part=2]") {
  PNG expected;  expected.readFromFile("tests/expected-sort_1.png");

  srand(225);

  BlockPNG b;
  b.readFromFile("tests/alma.png");

  int d = 60;
  vector<int> v = buildVector(b, d);
  random_shuffle(v.begin(), v.end());

  List<int> img_srt(v.begin(), v.end());
  img_srt.sort();
  vector<int> v2(img_srt.begin(), img_srt.end());

  PNG b3 = b.genImg(v2, d);
  b3.writeToFile("actual-sort_1.png");
  INFO("Output image `b3` saved as actual-sort_1.png");

  REQUIRE( b3 == expected );
}

TEST_CASE("List::sort #2", "[weight=1][part=2]") {
  PNG expected;  expected.readFromFile("tests/expected-sort_2.png");

  srand(225);

  BlockPNG b;
  b.readFromFile("tests/alma.png");

  int d = 1;
  vector<int> v = buildVector(b, d);
  random_shuffle(v.begin(), v.end());

  List<int> img_srt(v.begin(), v.end());
  img_srt.sort();
  vector<int> v2(img_srt.begin(), img_srt.end());

  PNG b3 = b.genImg(v2, d);
  b3.writeToFile("actual-sort_2.png");
  INFO("Output image `b3` saved as actual-sort_2.png");

  REQUIRE( b3 == expected );
}
