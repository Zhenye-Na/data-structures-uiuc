#ifndef GridColorPicker_H
#define GridColorPicker_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using grid color picking algorithm
 */
class GridColorPicker : public ColorPicker {
public:
  GridColorPicker(HSLAPixel gridColor, HSLAPixel backgroundColor, unsigned spacing);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  HSLAPixel gridColor, backgroundColor;
  unsigned spacing;
};

#endif
