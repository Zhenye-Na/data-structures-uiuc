#ifndef LAB_INTRO_H
#define LAB_INTRO_H

#include "cs225/PNG.h"
using namespace cs225;

PNG grayscale(PNG image);  
PNG createSpotlight(PNG image, int centerX, int centerY);
PNG illinify(PNG image);
PNG watermark(PNG firstImage, PNG secondImage);

#endif