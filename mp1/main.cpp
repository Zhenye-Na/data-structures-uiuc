#include <iostream>
#include <stdlib.h>

#include "mp1.h"
#include "cs225/PNG.h"

int main(int argc, char *argv[]) {
  if (argc == 2) {
    unsigned int width = (unsigned int)atoi(argv[1]);
    std::cout << "Calling myArt(" << width << ", " << width << ") and saving it as `art.png`." << std::endl;

    cs225::PNG png = myArt(width, width);
    png.writeToFile("art.png");
  } else {
    std::cout << "Rotating `in.png` as `out.png`" << std::endl;
    rotate("in.png", "out.png");
  }
  
  return 0;
}
