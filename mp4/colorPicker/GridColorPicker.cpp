#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "GridColorPicker.h"

using namespace cs225;

/**
 * GridColorPicker constructor
 */
GridColorPicker::GridColorPicker(
  HSLAPixel gridColor, HSLAPixel backgroundColor, unsigned spacing
) : gridColor(gridColor), backgroundColor(backgroundColor), spacing(spacing) { }

/**
 * Picks the color for pixel (x, y).
 * 
 * Color will be choosed as grid
 * 
 * @param x The x coordinate to pick a color for.
 * @param y The y coordinate to pick a color for.
 * @return The color selected for (x, y).
 */
HSLAPixel GridColorPicker::getColor(unsigned x, unsigned y) {
  if (x % spacing == 0 || y % spacing == 0) {
    return gridColor;
  } else {
    return backgroundColor;
  }
}
