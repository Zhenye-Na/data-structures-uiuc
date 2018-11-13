/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 *
 * Please see line.h for documentation of the Line class
 */

#include "line.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <vector>

using std::vector;

vector<double> Line::linearInterpolation(const Vector2& a, const Vector2& b)
{
    /* http://gabrielongraphics.blogspot.com/2005/09/drawing-line-segments.html */
    vector<double> values;

    const int num_steps = abs(static_cast<int>(b.x() - a.x()));

    if (num_steps == 0) {
        values.push_back(a.y());
    } else {
        const double slope = (b.y() - a.y()) / num_steps;

        double y = a.y();
        for (int i = 0; i < num_steps; i++) {
            values.push_back(y);
            y += slope;
        }
    }

    return values;
}

Line::Line(const Vector2& pa, const Vector2& pb, const HSLAPixel& pcolor)
    : a_(pa), b_(pb), color_(pcolor)
{
    /* Nothing see initialization list. */
}

void Line::draw(PNG* canvas) const
{
    /* http://gabrielongraphics.blogspot.com/2005/09/drawing-line-segments.html */
    const double delta_x = abs(static_cast<int>(b_.x() - a_.x()));
    const double delta_y = abs(static_cast<int>(b_.y() - a_.y()));
    HSLAPixel* pixel;

    if (delta_x > delta_y) {
        const Vector2* left = &a_;
        const Vector2* right = &b_;
        if (a_.isEastOf(b_)) {
            left = &b_;
            right = &a_;
        }

        vector<double> y_values = linearInterpolation(*left, *right);
        for (int x = static_cast<int>(left->x()); x < static_cast<int>(right->x()); x++) {
            const int y = static_cast<int>(y_values[static_cast<int>(x - left->x())]);
            pixel = &(canvas->getPixel(x, y));
            *pixel = this->color();
        }
    } else {
        const Vector2* small = &a_;
        const Vector2* large = &b_;
        if (a_.y() > b_.y()) {
            small = &b_;
            large = &a_;
        }

        const Vector2 flipped0(small->y(), small->x());
        const Vector2 flipped1(large->y(), large->x());

        vector<double> x_values = linearInterpolation(flipped0, flipped1);
        for (int y = static_cast<int>(small->y()); y < static_cast<int>(large->y()); y++) {
            const int x = static_cast<int>(x_values[static_cast<int>(y - small->y())]);
            pixel = &(canvas->getPixel(x, y));
            *pixel = this->color();
        }
    }
}

Vector2 Line::a() const
{
    return this->a_;
}

void Line::set_a(const Vector2& pa)
{
    this->a_ = pa;
}

Vector2 Line::b() const
{
    return this->b_;
}

void Line::set_b(const Vector2& pb)
{
    this->b_ = pb;
}

HSLAPixel Line::color() const
{
    return this->color_;
}

void Line::set_color(const HSLAPixel& pcolor)
{
    this->color_ = pcolor;
}
