/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 */

#include "cs225/PNG.h"
#include "color.h"
#include "rectangle.h"
#include "shape.h"
#include "vector2.h"

const char OUTPUT_FILE[] = "out.png";
const int WIDTH = 128;
const int HEIGHT = 128;
const Vector2 CENTER(WIDTH / 2, HEIGHT / 2);

int main()
{
    const int rectangle_width = 16;
    const int rectangle_height = 16;
    Vector2 rectangle_center(32, 16);
    // I can create a Rectangle using a Rectangle Pointer!
    Rectangle* rectangle = new Rectangle(rectangle_center, color::RED,
                                         rectangle_width, rectangle_height);

    rectangle_center.set_x(rectangle_center.x() + rectangle_width);
    // OR I can create a Rectangle using a Shape Pointer!!
    Shape* rectangle_shape = new Rectangle(rectangle_center, color::ORANGE,
                                           rectangle_width, rectangle_height);

    rectangle_center.set_x(rectangle_center.x() + rectangle_width);
    // OR I can create a Rectangle using a Drawable Pointer!!!
    Drawable* rectangle_drawable = new Rectangle(
        rectangle_center, color::YELLOW, rectangle_width, rectangle_height);

    // Since all these pointers point to something that is a Drawable type
    // lets make an array of drawable pointers
    size_t num_drawables = 3;
    Drawable** drawables = new Drawable*[num_drawables];
    drawables[0] = rectangle;
    drawables[1] = rectangle_shape;
    drawables[2] = rectangle_drawable;

    PNG canvas;
    canvas.resize(WIDTH, HEIGHT);

    // Since they are all drawable I can call draw on all of them
    for (size_t i = 0; i < num_drawables; i++) {
        drawables[i]->draw(&canvas);
    }

    canvas.writeToFile(OUTPUT_FILE);

    for (size_t i = 0; i < num_drawables; i++) {
        delete drawables[i];
        drawables[i] = NULL;
    }

    delete[] drawables;
    drawables = NULL;
    return 0;
}
