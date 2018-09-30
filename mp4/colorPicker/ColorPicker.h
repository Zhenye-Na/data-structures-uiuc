#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "../cs225/HSLAPixel.h"

using namespace cs225;

/**
 * The base class for different color picking algorithms
 * All color picking classes inherit from this class
 */
class ColorPicker {
public:
  /**
   * Class destructor
   */
  virtual ~ColorPicker() { }
  /**
   * Select a color for the given point (x, y)
   * All derived classes needs to implement this
   */
  virtual HSLAPixel getColor(unsigned x, unsigned y) = 0;
};

#endif