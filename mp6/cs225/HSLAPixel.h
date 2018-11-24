/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1
 */

#ifndef CS225_HSLAPIXEL_H_
#define CS225_HSLAPIXEL_H_

#include <iostream>
#include <sstream>

namespace cs225 {
  class HSLAPixel {
  public:
    double h; /**< Hue of the pixel, in degrees [0, 360). */
    double s; /**< Saturation of the pixel, [0, 1]. */
    double l; /**< Luminance of the pixel, [0, 1]. */
    double a; /**< Alpha of the pixel, [0, 1]. */

    /**
     * Constructs a default HSLAPixel.
     *
     * A default pixel is completely opaque (non-transparent) and white.
     * Opaque implies that the alpha component of the pixel is 1.0.
     * Lower alpha values are (semi-)transparent.
     */
    HSLAPixel();

    /**
     * Constructs an opaque HSLAPixel with the given hue, saturation,
     * and luminance values.
     *
     * @param hue Hue value for the new pixel, in degrees [0, 360).
     * @param saturation Saturation value for the new pixel, [0, 1].
     * @param luminance Luminance value for the new pixel, [0, 1].
     */
    HSLAPixel(double hue, double saturation, double luminance);

    /**
     * Constructs an HSLAPixel with the given hue, saturation,
     * luminance, and alpha values.
     *
     * @param hue Hue value for the new pixel, in degrees [0, 360).
     * @param saturation Saturation value for the new pixel, [0, 1].
     * @param luminance Luminance value for the new pixel, [0, 1].
     * @param alpha Alpha value for the new pixel, [0, 1].
     */
    HSLAPixel(double hue, double saturation, double luminance, double alpha);

    HSLAPixel & operator=(HSLAPixel const & other);
    bool operator== (HSLAPixel const & other) const ;
    bool operator!= (HSLAPixel const & other) const ;
    bool operator<  (HSLAPixel const & other) const ;
  };

  /**
   * Stream operator that allows pixels to be written to standard streams
   * (like cout).
   *
   * @param out Stream to write to.
   * @param pixel Pixel to write to the stream.
   */
  std::ostream & operator<<(std::ostream & out, HSLAPixel const & pixel);
  std::stringstream & operator<<(std::stringstream & out, HSLAPixel const & pixel);
}

#endif
