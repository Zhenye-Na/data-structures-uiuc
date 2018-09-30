#include <cmath>

#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "GradientColorPicker.h"

/**
 * GradientColorPicker constructor
 */
GradientColorPicker::GradientColorPicker(
  HSLAPixel color1, HSLAPixel color2, Point center, unsigned radius
) : color1(color1), color2(color2), center(center), radius(radius) { }

/**
 * Picks the color for pixel (x, y).
 *
 * The first color fades into the second color as you move from the initial
 * fill point, the center, to the radius. Beyond the radius, all pixels
 * should be just color2.
 *
 * You should calculate the distance between two points using the standard
 * euclidean distance formula.
 *
 * Then, scale each of the three channels (H, S, and L) from color1 to
 * color2 linearly from d = 0 to d = radius.
 *
 * @param x The x coordinate to pick a color for.
 * @param y The y coordinate to pick a color for.
 * @return The color selected for (x, y).
 */
HSLAPixel GradientColorPicker::getColor(unsigned x, unsigned y) {
  double dx = x - center.x;
  double dy = y - center.y;
  double d = sqrt((dx * dx) + (dy * dy));
  double pct = d / radius;

  if (pct >= 1) { return color2; }

  double h = color1.h - (color1.h * pct) + (color2.h * pct);
  double s = color1.s - (color1.s * pct) + (color2.s * pct);
  double l = color1.l - (color1.l * pct) + (color2.l * pct);

  return HSLAPixel(h, s, l);
}
