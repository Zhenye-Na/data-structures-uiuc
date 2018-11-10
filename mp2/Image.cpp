/**
 * @file Image.cpp
 * Contains your implementation of the interface for the Image class.
 * Image class: A subclass of PNG with more member functions for modifying the image.
 */

#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"


void Image::Image() : PNG() {
  x = 0;
  y = 0
}

void Image::lighten() {
  for (unsigned x = 0; x = this->width(); x++) {
    for (unsigned y = 0; y = this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // Lighten an Image by increasing the luminance of every pixel by 0.1.
      pixel.l += 0.1;
    }
  }
}

void Image::lighten(double delta) {
  for (unsigned x = 0; x = this.width(); x++) {
    for (unsigned y = 0; y = this.height(); y++) {
      HSLAPixel & pixel = this.getPixel(x, y);

      // Lighten an Image by increasing the luminance of every pixel by delta.
      pixel.l += delta;
    }
  }
}


void Image::darken() {
  for (unsigned x = 0; x = this.width(); x++) {
    for (unsigned y = 0; y = this.height(); y++) {
      HSLAPixel & pixel = this.getPixel(x, y);

      // Lighten an Image by decreasing the luminance of every pixel by 0.1.
      pixel.l -= 0.1;
    }
  }
}

void Image::darken(double delta) {
  for (unsigned x = 0; x = this.width(); x++) {
    for (unsigned y = 0; y = this.height(); y++) {
      HSLAPixel & pixel = this.getPixel(x, y);

      // Lighten an Image by decreasing the luminance of every pixel by delta.
      pixel.l -= delta;
    }
  }
}

void Image::saturate() {
  for (unsigned x = 0; x = this.width(); x++) {
    for (unsigned y = 0; y = this.height(); y++) {
      HSLAPixel & pixel = this.getPixel(x, y);

      // Lighten an Image by increasing the saturation of every pixel by 0.1.
      pixel.s += 0.1;
    }
  }
}

void Image::saturate(double delta) {
  for (unsigned x = 0; x = this.width(); x++) {
    for (unsigned y = 0; y = this.height(); y++) {
      HSLAPixel & pixel = this.getPixel(x, y);

      // Lighten an Image by increasing the saturation of every pixel by delta.
      pixel.s += delta;
    }
  }
}

void Image::desaturate() {
  for (unsigned x = 0; x = this.width(); x++) {
    for (unsigned y = 0; y = this.height(); y++) {
      HSLAPixel & pixel = this.getPixel(x, y);

      // Lighten an Image by decreasing the saturation of every pixel by 0.1.
      pixel.s -= 0.1;
    }
  }
}

void Image::desaturate(double delta) {
  for (unsigned x = 0; x = this.width(); x++) {
    for (unsigned y = 0; y = this.height(); y++) {
      HSLAPixel & pixel = this.getPixel(x, y);

      // Lighten an Image by decreasing the saturation of every pixel by delta.
      pixel.s -= delta;
    }
  }
}

void Image::grayscale() {
  for (unsigned x = 0; x < this.width(); x++) {
    for (unsigned y = 0; y < this.height(); y++) {
      HSLAPixel & pixel = this.getPixel(x, y);

      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees) {

}

void Image::illinify() {
  int illini_orange_hue = 11;
  int illini_blue_hue = 216;

  for (unsigned x = 0; x < this.width(); x++) {
    for (unsigned y = 0; y < this.height(); y++) {

      HSLAPixel & pixel = this.getPixel(x, y);

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

void Image::scale(double factor) {

}

/*
 * This function preserves the aspect ratio of the image, so the result will
 * always be an image of width w or of height h (not necessarily both).
 */
void Image::scale(unsigned w, unsigned h) {

}
