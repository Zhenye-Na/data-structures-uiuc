/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 */

#include <iostream>

#include "cs225/PNG.h"
#include "flower.h"

using namespace std;

int main()
{
    const int canvas_width = 128;
    const int canvas_height = 128;

    PNG canvas;
    canvas.resize(canvas_width, canvas_height);

    const Vector2 flower_center(canvas_width / 2, canvas_height / 2);

    Drawable* flower = new Flower(flower_center);

    /* TODO: For some reason this flower is not drawing correctly?  The stem,
     * pistil, and leaf are all being drawn as big giant X's. */
    flower->draw(&canvas);

    canvas.writeToFile("test_slicing.png");

    delete flower;
    return 0;
}
