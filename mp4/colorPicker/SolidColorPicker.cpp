#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "SolidColorPicker.h"

using namespace cs225;

/**
 * SolidColorPicker constructor
 */
SolidColorPicker::SolidColorPicker(HSLAPixel color) : color(color) { }

/**
 * Picks the color for pixel (x, y).
 *
 * The color will be a constant for all the points
 *
 * @param x The x coordinate to pick a color for.
 * @param y The y coordinate to pick a color for.
 * @return The color selected for (x, y).
 */
HSLAPixel SolidColorPicker::getColor(unsigned x, unsigned y) {
  return color;
}
