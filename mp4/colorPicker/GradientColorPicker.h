#ifndef GradientColorPicker_H
#define GradientColorPicker_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using gradient color picking algorithm
 */
class GradientColorPicker : public ColorPicker {
public:
  GradientColorPicker(HSLAPixel color1, HSLAPixel color2, Point center, unsigned radius);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  HSLAPixel color1;
  HSLAPixel color2;
  Point center;
  unsigned radius;
};

#endif
