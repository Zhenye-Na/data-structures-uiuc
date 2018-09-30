/**
 * @file Point.h
 * every 2D point of the image is represented by a Point class
 * you need to trverse all the points of the image
 */
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <sstream>

/**
 * Simple Point class containing a public unsigned `x` and `y` for representing 2D points on an image.
 */
struct Point {
  unsigned x;
  unsigned y;

  /**
   * Default constructor, set the point to (0, 0)
   */
  Point() : Point(0, 0) { }
  /**
   * Constructor
   * @param x coordinate of a point
   * @param y coordinate of a point
   */
  Point(unsigned x, unsigned y) : x(x), y(y) { }

  /**
   * overload operator <
   * @param other The other point
   * @return True for smaller, false for otherwise
   */
  bool operator<(const Point &other) const {
    return (x < other.x || y < other.y);
  }

  /**
   * overload operator ==
   * @param other The other point
   * @return True for smaller, false for otherwise
   */
  bool operator==(const Point &other) const {
    return (x == other.x && y == other.y);
  }
};

  /**
   * overload operator <<
   * print out a point
   * @param out Output stream
   * @param point The point to print
   * @return Output stream
   */
inline std::ostream & operator<<(std::ostream & out, Point const & point) {
  out << "(" << point.x << ", " << point.y << ")";
  return out;
}

#endif
