/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 */

#include <iostream>

#include "color.h"
#include "rectangle.h"
#include "vector2.h"

using namespace std;

int main()
{
    const int canvas_width = 128;
    const int canvas_height = 128;

    PNG canvas;
    canvas.resize(canvas_width, canvas_height);

    Vector2 rectangle_center(canvas_width / 2, canvas_height / 2);
    const int rectangle_width = canvas_width / 4;
    const int rectangle_height = canvas_height / 4;
    Rectangle* rectangle = new Rectangle(rectangle_center, color::BLUE,
                                         rectangle_width, rectangle_height);

    rectangle->draw(&canvas);

    const int rectangle_perimeter = rectangle->perimeter();
    cout << "Rectangle's Perimeter = " << rectangle_perimeter << endl;
    const int rectangle_area = rectangle->area();
    cout << "Rectangle's Area = " << rectangle_area << endl;

    /* But we can treat a Rectangle just like a Shape using a Shape pointer */
    Shape* shape = rectangle;
    const int shape_perimeter = shape->perimeter();
    cout << "Shape's Perimeter = " << shape_perimeter << endl;
    const int shape_area = shape->area();
    cout << "Shape' Area = " << shape_area << endl;

    /* TODO: For some reason the shape's area and perimeter is different from
     * triangle's area and perimeter even though they are pointing to the same
     * object!  Can you this this so they are the same WITHOUT changing the
     * shape's type from a Shape pointer to a Triangle pointer? */
    if (rectangle_perimeter == shape_perimeter) {
        cout << "The Perimeters are the same!" << endl;
    } else {
        cout << "The Perimeters are NOT the same." << endl;
    }

    if (rectangle_area == shape_area) {
        cout << "The Areas are the same!" << endl;
    } else {
        cout << "The Areas are NOT the same." << endl;
    }

    canvas.writeToFile("test_virtual.png");

    delete rectangle;

    return 0;
}
