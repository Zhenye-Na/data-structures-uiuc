#include "../cs225/HSLAPixel.h"

#include "ColorPicker.h"
#include "RainbowColorPicker.h"

/**
 * RainbowColorPicker constructor
 */
RainbowColorPicker::RainbowColorPicker(double increment)
  : hue(0), increment(increment) { }

/**
 * Picks the color for pixel (x, y).
 *
 *
 * @param x The x coordinate to pick a color for.
 * @param y The y coordinate to pick a color for.
 * @return The color selected for (x, y).
 */
HSLAPixel RainbowColorPicker::getColor(unsigned x, unsigned y) {
  HSLAPixel pixel(hue, 1, 0.5);
  hue += increment;
  if (hue >= 360) { hue -= 360; }
  return pixel;
}
