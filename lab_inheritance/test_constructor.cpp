/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 */

#include <iostream>

#include "cs225/PNG.h"
#include "color.h"
#include "shape.h"
#include "circle.h"
#include "vector2.h"

using namespace std;
using namespace cs225;

int main()
{
    const int canvas_width = 128;
    const int canvas_height = 128;

    PNG canvas;
    canvas.resize(canvas_width, canvas_height);

    const HSLAPixel circle_color = color::ORANGE;
    const Vector2 circle_center(32, 32);
    const int circle_radius = 16;
    Circle* circle = new Circle(circle_center, circle_color, circle_radius);

    circle->draw(&canvas);

    canvas.writeToFile("test_constructor.png");

    /* TODO: For some reason the circle is NOT constructed with the proper color
     * and center position.
     * Can you make it so the circle is constructed with the proper color and
     * center position WITH OUT using set_center() or set_color()? */
    const bool correct_color = (circle->color() == circle_color);

    if (correct_color) {
        cout << "Circle's color is correct!" << endl;
    } else {
        cout << "Circle's color is NOT correct!" << endl;
    }

    const bool correct_center = circle->center() == circle_center;
    if (correct_center) {
        cout << "Circle's center is correct!" << endl;
    } else {
        cout << "Circle's center is NOT correct!" << endl;
    }

    delete circle;
    circle = NULL;

    return 0;
}
