/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 *
 * Please see shape.h for documentation of the Shape class
 */

#include "shape.h"

#include "color.h"
#include "line.h"

const Vector2 DEFAULT_CENTER(64, 64);
const HSLAPixel DEFAULT_COLOR = color::BLACK;

Shape::Shape() : center_(DEFAULT_CENTER), color_(DEFAULT_COLOR)
{
    /* Nothing.  See initialization list. */
}

Shape::Shape(const Vector2& pcenter, const HSLAPixel& pcolor)
    : center_(pcenter), color_(pcolor)
{
    /* Nothing.  See initialization list. */
}

int Shape::area() const
{
    /* Shape's don't have an area since they cannot be made */
    return 0;
}

int Shape::perimeter() const
{
    /* Shape's don't have a perimeter since they cannot be made */
    return 0;
}

bool Shape::contains(const Vector2& p) const
{
    /* Default shapes don't contain any points */
    return false;
}

Vector2 Shape::center() const
{
    return this->center_;
}

void Shape::set_center(const Vector2& pcenter)
{
    this->center_ = pcenter;
}

HSLAPixel Shape::color() const
{
    return this->color_;
}

void Shape::draw(PNG* canvas) const
{
    const Vector2 top_left(this->center().x() - 8, this->center().y() - 8);
    const Vector2 top_right(this->center().x() + 8, this->center().y() - 8);
    const Vector2 bottom_left(this->center().x() - 8, this->center().y() + 8);
    const Vector2 bottom_right(this->center().x() + 8, this->center().y() + 8);

    const Line foward_slash(bottom_left, top_right, color::RED);
    foward_slash.draw(canvas);

    const Line backward_slash(top_left, bottom_right, color::RED);
    backward_slash.draw(canvas);
}
