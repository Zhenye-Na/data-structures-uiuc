/**
 * @file Image.cpp
 * Contains your implementation of the interface for the Image class.
 * Image class: A subclass of PNG with more member functions for modifying the image.
 */

#include <algorithm>

#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

void Image::lighten() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // Lighten an Image by increasing the luminance of every pixel by 0.1.
      pixel.l += 0.1;
      if (pixel.l > 1) {
        pixel.l = 1;
      }
    }
  }
}


void Image::lighten(double delta) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // Lighten an Image by increasing the luminance of every pixel by delta.
      pixel.l += delta;
      if (pixel.l > 1) {
        pixel.l = 1;
      }
    }
  }
}


void Image::darken() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // Lighten an Image by decreasing the luminance of every pixel by 0.1.
      pixel.l -= 0.1;
      if (pixel.l < 0) {
        pixel.l = 0;
      }
    }
  }
}


void Image::darken(double delta) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // Lighten an Image by decreasing the luminance of every pixel by delta.
      pixel.l -= delta;
      if (pixel.l < 0) {
        pixel.l = 0;
      }
    }
  }
}


void Image::saturate() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // Lighten an Image by increasing the saturation of every pixel by 0.1.
      pixel.s += 0.1;
      if (pixel.s > 1) {
        pixel.s = 1;
      }
    }
  }
}


void Image::saturate(double delta) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // Lighten an Image by increasing the saturation of every pixel by delta.
      pixel.s += delta;
      if (pixel.s > 1) {
        pixel.s = 1;
      }
    }
  }
}


void Image::desaturate() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // Lighten an Image by decreasing the saturation of every pixel by 0.1.
      pixel.s -= 0.1;
      if (pixel.s < 0) {
        pixel.s = 0;
      }
    }
  }
}


void Image::desaturate(double delta) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // Lighten an Image by decreasing the saturation of every pixel by delta.
      pixel.s -= delta;
      if (pixel.s < 0) {
        pixel.s = 0;
      }
    }
  }
}


void Image::grayscale() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s = 0;
    }
  }
}


/*
 * Rotates the color wheel (hue) by degrees.
 */
void Image::rotateColor(double degrees) {

  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      pixel.h += degrees;

      if (pixel.h > 360) {
        pixel.h = pixel.h - 360;
      } else if (pixel.h < 0) {
        pixel.h = pixel.h + 360;
      }
    }
  }
}


void Image::illinify() {
  int illini_orange_hue = 11;
  int illini_blue_hue = 216;

  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {

      HSLAPixel & pixel = this->getPixel(x, y);

      if (pixel.h < illini_blue_hue && pixel.h > illini_orange_hue) {

        if ( illini_blue_hue - pixel.h < pixel.h - illini_orange_hue ) {
          pixel.h = illini_blue_hue;
        } else {
          pixel.h = illini_orange_hue;
        }
      }

      else if (pixel.h < 360 && pixel.h > illini_blue_hue) {
        int dist_blue = pixel.h - illini_blue_hue;
        int dist_orge = 360 - pixel.h + illini_orange_hue;

        if (dist_blue < dist_orge) {
          pixel.h = illini_blue_hue;
        } else {
          pixel.h = illini_orange_hue;
        }
      }

      else {
        pixel.h = illini_orange_hue;
      }

    }
  }

}


// def nearestNeighborScaling( source, newWid, newHt ):
//     target = makeEmptyPicture(newWid, newHt)
//     width = getWidth( source )
//     height = getHeight( source )
//     for x in range(0, newWid):
//       for y in range(0, newHt):
//         srcX = int( round( float(x) / float(newWid) * float(width) ) )
//         srcY = int( round( float(y) / float(newHt) * float(height) ) )
//         srcX = min( srcX, width-1)
//         srcY = min( srcY, height-1)
//         tarPix = getPixel(target, x, y )
//         srcColor = getColor( getPixel(source, srcX, srcY) )
//         setColor( tarPix, srcColor)
//
//     return target


/*
 * Scale the Image by a given factor.
 *
 * For example:
 *  A factor of 1.0 does not change the iamge.
 *  A factor of 0.5 results in an image with half the width and half the height.
 *  A factor of 2 results in an image with twice the width and twice the height.
 */
void Image::scale(double factor) {
  unsigned int target_width  = (unsigned int)(factor * this->width());
  unsigned int target_height = (unsigned int)(factor * this->height());
  unsigned width = this->width();
  unsigned height = this->height();

  Image *copyImage = this;
  this->resize(target_width, target_height);

  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {

      unsigned srcX = (unsigned)( x / target_width) * width;
      unsigned srcY = (unsigned)( x / target_height) * height;

      if (srcX > width - 1) {
        srcX = width - 1;
      }

      if (srcY > height - 1) {
        srcY = height - 1;
      }

      HSLAPixel & newPixel = this->getPixel(x, y);
      HSLAPixel & oldPixel = copyImage->getPixel(srcX, srcY);
      newPixel = oldPixel;

      // unsigned int oldX = (unsigned int)(x / factor);
      // unsigned int oldY = (unsigned int)(y / factor);
      //
      // if (oldX < copyImage->width() && oldY < copyImage->height()) {
      //   HSLAPixel & oldPixel = copyImage->getPixel(oldX, oldY);
      //   HSLAPixel & newPixel = this->getPixel(x, y);
      //
      //   newPixel = oldPixel;
      // }
    }
  }
}


/*
 * This function preserves the aspect ratio of the image, so the result will
 * always be an image of width w or of height h (not necessarily both).
 */
void Image::scale(unsigned w, unsigned h) {
  unsigned original_width = this->width();
  double factor = (double)(w / original_width);
  scale(w);
}
