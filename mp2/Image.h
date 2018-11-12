/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#ifndef IMAGE_H_
#define IMAGE_H_

namespace cs225 {
  class Image: public PNG {
  public:

    /*
     * Lighten an Image by increasing the luminance of every pixel by 0.1.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    void lighten();

    /*
     * Lighten an Image by increasing the luminance of every pixel by amount.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    void lighten(double amount);

    /*
     * Darken an Image by decreasing the luminance of every pixel by 0.1.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    void darken();

    /*
     * Darken an Image by decreasing the luminance of every pixel by amount.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    void darken(double amount);

    /*
     * Darken an Image by increasing the saturation of every pixel by 0.1.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    void saturate();

    /*
     * Darken an Image by increasing the saturation of every pixel by amount.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    void saturate(double amount);

    /*
     * Darken an Image by decreasing the saturation of every pixel by 0.1.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    void desaturate();

    /*
     * Darken an Image by decreasing the saturation of every pixel by amount.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    void desaturate(double amount);

    /*
     * Turn the image to grayscale
     */
    void grayscale();

    /*
     * Rotates the color wheel by degrees.
     * This function ensures that the hue remains in the range [0, 360].
     */
    void rotateColor(double degrees);

    /*
     * Illinify the image.
     */
    void illinify();

    /*
     * Scale the Image by a given factor.
     */
    void scale(double factor);

    /*
     * Scales the image to fit within the size (w x h).
     * This function preserves the aspect ratio of the image, so the result will
     * always be an image of width w or of height h (not necessarily both).
     */
    void scale(unsigned w, unsigned h);

  };
}

#endif
