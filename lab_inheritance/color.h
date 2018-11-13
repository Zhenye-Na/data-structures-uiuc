/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 */

#ifndef COLOR_H_
#define COLOR_H_

#include "cs225/PNG.h"
using namespace cs225;

namespace color
{

    /* Format in initialization is hue, saturation, luminance, alpha */
    const HSLAPixel WHITE(0, 0, 1);
    const HSLAPixel BLACK(0, 0, 0);
    const HSLAPixel GRAY(33, 4.1/100.0, 56.7/100.0);
    const HSLAPixel RED(0, 1, 0.5);
    const HSLAPixel ORANGE(30, 1, 0.5);
    const HSLAPixel YELLOW(60, 1, 0.5);
    const HSLAPixel GREEN(120, 1, 0.5);
    const HSLAPixel TURQUOISE(120, 1, 0.5);
    const HSLAPixel BLUE(240, 1, 0.5);
    const HSLAPixel PURPLE(270, 1, 0.5);
    const HSLAPixel PINK(299, 96.9/100.0, 74.3/100.0);

} // namespace color

#endif // COLOR_H_
