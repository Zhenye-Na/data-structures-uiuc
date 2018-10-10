/**
 * tileimage.cpp (v2)
 * Impl of the TileImage class.
 *
 * @author Wade Fagen-Ulmschneider (http://waf.cs.illinois.edu/)
 * @date Fall 2017
 */

#include <algorithm>
#include <cmath>

#include "tileimage.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace std;
using namespace cs225;

#ifndef M_PI
constexpr double M_PI = 3.14159265358979323846;
#endif

TileImage::TileImage() : image_(1, 1) {
    averageColor_ = image_.getPixel(0, 0);
}

TileImage::TileImage(const PNG& source) : image_(cropSourceImage(source)) {
    averageColor_ = calculateAverageColor();
}

PNG TileImage::cropSourceImage(const PNG& source) {
    int height = source.height();
    int width = source.width();
    int resolution = min(width, height);

    int startX = 0;
    int startY = 0;

    if (width != height) {
        if (height > width)
            startY = (height - width) / 2;
        else
            startX = (width - width) / 2;
    }

    PNG cropped(resolution, resolution);

    for (int y = 0; y < resolution; y++)
        for (int x = 0; x < resolution; x++)
            cropped.getPixel(x, y) = source.getPixel(startX + x, startY + y);

    return cropped;
}

HSLAPixel TileImage::calculateAverageColor() const {
    double h_sin = 0, h_cos = 0, s = 0, l = 0;

    for (unsigned y = 0; y < image_.height(); y++) {
        for (unsigned x = 0; x < image_.width(); x++) {
            HSLAPixel & pixel = image_.getPixel(x, y);
            double h_rad = pixel.h * M_PI / 180;
            h_sin += sin( h_rad );
            h_cos += cos( h_rad );
            s += pixel.s;
            l += pixel.l;
        }
    }

    unsigned numPixels = image_.width() * image_.height();

    HSLAPixel color;
    color.h = atan2(h_sin, h_cos) * 180 / M_PI;
    if (color.h < 0) {
        color.h += 360;
    }
    color.s = s / numPixels;
    color.l = l / numPixels;
    return color;
}

void TileImage::generateResizedImage(int startX, int startY, int resolution) {

    // set the resized_ image to size: resolution x resolution
    resized_.resize(resolution, resolution);

    // If possible, avoid floating point comparisons. This helps ensure that
    // students' photomosaic's are diff-able with solutions
    if (getResolution() % resolution == 0) {
        int scalingRatio = getResolution() / resolution;

        for (int x = 0; x < resolution; x++) {
            for (int y = 0; y < resolution; y++) {
                int pixelStartX = (x)     * scalingRatio;
                int pixelEndX   = (x + 1) * scalingRatio;
                int pixelStartY = (y)     * scalingRatio;
                int pixelEndY   = (y + 1) * scalingRatio;

                resized_.getPixel(x, y) = getScaledPixelInt(pixelStartX, pixelEndX, pixelStartY, pixelEndY);
            }
        }
    } else { // scaling is necessary
        double scalingRatio = static_cast<double>(getResolution()) / resolution;

        for (int x = 0; x < resolution; x++) {
            for (int y = 0; y < resolution; y++) {
                double pixelStartX = (double)(x)     * scalingRatio;
                double pixelEndX   = (double)(x + 1) * scalingRatio;
                double pixelStartY = (double)(y)     * scalingRatio;
                double pixelEndY   = (double)(y + 1) * scalingRatio;

                resized_.getPixel(x, y) = getScaledPixelDouble(pixelStartX, pixelEndX, pixelStartY, pixelEndY);
            }
        }
    }
    
}    



void TileImage::paste(PNG& canvas, int startX, int startY, int resolution) {
    // check if not resized
    if (resized_.width() == 0) {
        generateResizedImage(startX, startY, resolution);
    }

    for (int x = 0; x < resolution; x++) {
        for (int y = 0; y < resolution; y++) {
            canvas.getPixel(startX + x, startY + y) = resized_.getPixel(x, y);
        }
    }
}



HSLAPixel TileImage::getScaledPixelDouble(double startX, double endX,
        double startY, double endY) const
{
    double leftFrac = 1.0 - frac(startX);
    double rightFrac = frac(endX);
    double topFrac = 1.0 - frac(startX);
    double bottomFrac = frac(endX);

    int startXint = static_cast<int>(startX);
    int endXint = static_cast<int>(ceil(endX));
    int startYint = static_cast<int>(startY);
    int endYint = static_cast<int>(ceil(endY));

    double h_sin = 0, h_cos = 0, s = 0, l = 0;
    double totalPixels = 0.0;

    for (int x = startXint; x < endXint; x++) {
        for (int y = startYint; y < endYint; y++) {
            double weight = 1.0;
            if (x == startXint) weight *= leftFrac;
            if (x == endXint)   weight *= rightFrac;
            if (y == startYint) weight *= topFrac;
            if (y == endYint)   weight *= bottomFrac;

            HSLAPixel & pixel = image_.getPixel(x, y);
            double h_rad = pixel.h * M_PI / 180;
            h_sin += sin( h_rad ) * weight;
            h_cos += cos( h_rad ) * weight;
            s += pixel.s * weight;
            l += pixel.l * weight;

            totalPixels += weight;
        }
    }

    HSLAPixel color;
    color.h = atan2(h_sin, h_cos) * 180 / M_PI;
    if (color.h < 0) {
        color.h += 360;
    }
    color.s = s / totalPixels;
    color.l = l / totalPixels;
    return color;
}

HSLAPixel TileImage::getScaledPixelInt(int startXint, int endXint,
        int startYint, int endYint) const
{
    double h_sin = 0, h_cos = 0, s = 0, l = 0;
    double totalPixels = 0;

    for (int x = startXint; x < endXint; x++) {
        for (int y = startYint; y < endYint; y++) {
            HSLAPixel & pixel = image_.getPixel(x, y);
            double h_rad = pixel.h * M_PI / 180;
            h_sin += sin( h_rad );
            h_cos += cos( h_rad );
            s += pixel.s;
            l += pixel.l;

            totalPixels++;
        }
    }

    HSLAPixel color;
    color.h = atan2(h_sin, h_cos) * 180 / M_PI;
    if (color.h < 0) {
        color.h += 360;
    }
    color.s = s / totalPixels;
    color.l = l / totalPixels;
    return color;
}
