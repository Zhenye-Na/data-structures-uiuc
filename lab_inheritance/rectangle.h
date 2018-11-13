/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "shape.h"

/**
 * @brief The Rectangle class is a subclass of Shape and represents a rectangle
 * in 2D space
 */
class Rectangle : public Shape
{
  private:
    int width_;
    int height_;

  public:
    /**
     * @brief Constructs a new Rectangle with the given center, color, height,
     *  and width
     *
     * @param center Vector2 of the Rectangle
     * @param color of the Rectangle
     * @param width in pixels
     * @param height in pixels
     */
    Rectangle(const Vector2& center, const HSLAPixel& color, int width,
              int height);

    /**
     * @brief Computes and returns the area of the Rectangle in pixels
     *
     * @return the area of the Rectangle in pixels
     */
    int area() const;

    /**
     * @brief Computes and returns the perimeter of the Rectangle in pixels
     *
     * @return the perimeter of the Rectangle in pixels
     */
    int perimeter() const;

    /**
     * @brief Checks to see if the given Vector2 p is inside of the Rectangle
     *
     * @param p Vector2
     *
     * @return true if p is inside of the Rectangle
     */
    bool contains(const Vector2& p) const;

    /**
     * @brief Draws the Rectangle onto the canvas
     *
     * @param canvas to draw onto
     */
    void draw(PNG* canvas) const;

    /**
     * @brief Gets the width of the Rectangle in pixels
     *
     * @return the width of the Rectangle in pixels
     */
    int width() const;

    /**
     * @brief Sets the width of the Rectangle in pixels
     *
     * @param width the new width of the Rectangle in pixels
     */
    void set_width(int width);

    /**
     * @brief Gets the height of the Rectangle in pixels
     *
     * @return the height of the Rectangle in pixels
     */
    int height() const;

    /**
     * @brief Sets the height of the Rectangle in pixels
     *
     * @param height the new height of the Rectangle in pixels
     */
    void set_height(int height);
};

#endif // RECTANGLE_H_
