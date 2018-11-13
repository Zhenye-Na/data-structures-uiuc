/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "cs225/PNG.h"
using namespace cs225;

/**
 * @brief A pure virtual interface class that can draw itself to a canvas.
 */
class Drawable
{
  public:
    ~Drawable()
    { /* Nothing */
    }

    /**
     * @brief This method will draw the object onto the canvas.
     *
     * @param canvas to draw onto.
     */
    virtual void draw(PNG* canvas) const = 0;
};

#endif // DRAWABLE_H_
