/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#ifndef IMAGE_H_
#define IMAGE_H_

class Image: public PNG {
  public:

    Image();


    /*
     * Lighten an Image by increasing the luminance of every pixel by 0.1.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    lighten();

    /*
     * Lighten an Image by increasing the luminance of every pixel by amount.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    lighten(double amount)

    /*
     * Darken an Image by decreasing the luminance of every pixel by 0.1.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    darken()

    /*
     * Darken an Image by decreasing the luminance of every pixel by amount.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    darken(double amount);

    /*
     * Darken an Image by increasing the saturation of every pixel by 0.1.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    saturate();

    /*
     * Darken an Image by increasing the saturation of every pixel by amount.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    saturate(double amount);

    /*
     * Darken an Image by decreasing the saturation of every pixel by 0.1.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    desaturate();

    /*
     * Darken an Image by decreasing the saturation of every pixel by amount.
     * This function ensures that the luminance remains in the range [0, 1].
     */
    desaturate(double amount);

    /*
     * Turn the image to grayscale
     */
    grayscale();

    /*
     * Rotates the color wheel by degrees.
     * This function ensures that the hue remains in the range [0, 360].
     */
    rotateColor(double degrees)

    /*
     * Illinify the image.
     */
    illinify();

    /*
     * Scale the Image by a given factor.
     */
    scale(double factor);

    /*
     * Scales the image to fit within the size (w x h).
     * This function preserves the aspect ratio of the image, so the result will
     * always be an image of width w or of height h (not necessarily both).
     */
    scale(unsigned w, unsigned h);

    int x;
    int y;
}

#endif
