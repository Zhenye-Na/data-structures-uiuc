/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "drawable.h"
#include "vector2.h"

/**
 * @brief An abstract base class that represents a Shape which has an area,
 * perimeter, color, and can contain Vector2s.  Shapes are also drawable, so
 * they are expected to know how to draw them selves to a PNG.
 */
class Shape : public Drawable
{
  protected:
    Vector2 center_;

  private:
    HSLAPixel color_;

  public:
    /**
     * @brief Constructs a new Shape with a default color and center
     */
    Shape();

    /**
     * @brief Constructs a new Shape with the given center and color
     *
     * @param center Vector2 of the new Shape
     * @param color of the new Shape
     */
    Shape(const Vector2& center, const HSLAPixel& color);

    ~Shape()
    { /* Nothing */
    }

    /**
     * @brief Computes and returns the area of the Shape in pixels
     *
     * @return the area (in pixels) of the Shape
     */
    int area() const;

    /**
     * @brief Computes and returns the perimeter of the Shape in pixels
     *
     * @return the perimeter (in pixels) of the Shape
     */
    int perimeter() const;

    /**
     * @brief Checks to see if the Vector2 p is contained inside of the Shape
     *
     * @param p Vector2 to check if it is contained inside the Shape or not
     *
     * @return true if Vector2 p is inside of the Shape
     */
    bool contains(const Vector2& p) const;

    /**
     * @brief Gets the center Vector2 of the Shape
     *
     * @return the center Vector2 of the Shape
     */
    Vector2 center() const;

    /**
     * @brief Sets the center Vector2 of the Shape
     *
     * @param center the new center Vector2 of the Shape
     */
    virtual void set_center(const Vector2& center);

    /**
     * @brief Gets the color of the Shape
     *
     * @return the HSLAPixel representing the color of the Shape
     */
    HSLAPixel color() const;

    void draw(PNG* canvas) const;
};

#endif // SHAPE_H_
