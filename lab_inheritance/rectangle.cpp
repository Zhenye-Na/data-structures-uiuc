/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 *
 * Please see rectangle.h for documentation of the Rectangle class
 */

#include "rectangle.h"

#include <cstdio>

Rectangle::Rectangle(const Vector2& pcenter, const HSLAPixel& pcolor,
                     int pwidth, int pheight)
    : Shape(pcenter, pcolor), width_(pwidth), height_(pheight)
{
    /* Nothing.  See initialization list. */
}

int Rectangle::area() const
{
    return this->width_ * this->height_;
}

int Rectangle::perimeter() const
{
    return 2 * (this->width_ + this->height_);
}

bool Rectangle::contains(const Vector2& p) const
{
    const Vector2 top_left_corner(center().x() - (width_ - 1) / 2,
                                  center().y() - (height_ - 1) / 2);
    const Vector2 bottom_right_corner(center().x() + width_ / 2,
                                      center().y() + height_ / 2);
    const bool inside_top_left
        = (p.x() == top_left_corner.x() || p.y() == top_left_corner.y()
           || p.isSouthEastOf(top_left_corner));
    const bool inside_bottom_right
        = (p.x() == bottom_right_corner.x() || p.y() == bottom_right_corner.y()
           || p.isNorthWestOf(bottom_right_corner));
    return inside_top_left && inside_bottom_right;
}

void Rectangle::draw(PNG* canvas) const
{
    HSLAPixel * pixel;
    const int x_offset
        = static_cast<int>(this->center().x() - (this->width_ / 2));
    const int y_offset
        = static_cast<int>(this->center().y() - (this->height_ / 2));
    for (int i = 0; i < this->width_; i++) {
        for (int j = 0; j < this->height_; j++) {
            pixel = &((*canvas).getPixel(x_offset + i, y_offset + j));
            *pixel = this->color();
        }
    }
}

int Rectangle::width() const
{
    return this->width_;
}

void Rectangle::set_width(int pwidth)
{
    this->width_ = pwidth;
}

int Rectangle::height() const
{
    return this->height_;
}

void Rectangle::set_height(int pheight)
{
    this->height_ = pheight;
}
