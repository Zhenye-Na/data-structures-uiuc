#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>

using namespace cs225;

// sets up the output image
PNG* setupOutput(unsigned w, unsigned h) {
  PNG* image = new PNG(w, h);
  return image;
}


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2: Rotate an Image

  // Load inputImage
  PNG* inputImage = new PNG();
  inputImage->readFromFile(inputFile);
  unsigned width = inputImage->width();
  unsigned height = inputImage->height();

  // Create outputImage
  PNG* outputImage = nullptr;
  outputImage = setupOutput(width, height);


  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      HSLAPixel * inputPixel = inputImage->getPixel(x, y);
      HSLAPixel * outputPixel = outputImage->getPixel(width-1-x, height-1-y);

      *outputPixel = *inputPixel;
    } 
  }

  // Save the output file
  outputImage->writeToFile(outputFile);

  // Clean up memory
  delete inputImage;
  delete outputImage;
}


PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // Part 3: Getting Creative

  return png;
}
