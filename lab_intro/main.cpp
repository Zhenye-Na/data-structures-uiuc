/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
 * @author CS 225: Data Structures
**/

#include "lab_intro.h"
#include "cs225/PNG.h"

int main() {
  cs225::PNG png, png2, result;

  png.readFromFile("alma.png");
  result = grayscale(png);
  result.writeToFile("out-grayscale.png");
  
  result = createSpotlight(png, 450, 150);
  result.writeToFile("out-spotlight.png");

  result = illinify(png);
  result.writeToFile("out-illinify.png");

  png2.readFromFile("overlay.png");
  result = watermark(png, png2);
  result.writeToFile("out-watermark.png");
  
  return 0;
}
