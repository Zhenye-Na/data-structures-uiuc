/**
 * @file point.h
 * Definition of a Point class for k dimensional points.
 *
 * @author Wade Fagen-Ulmschneider <waf@illinois.edu> & Arman Tajback
 * @date Fall 2017
 * @note Based on Matt Sachtler's MP6 Point class.
 */

#ifndef __POINT_H__
#define __POINT_H__

#include <cstdarg>
#include <iostream>
#include <stdexcept>

using std::out_of_range;
using std::cout;
using std::endl;


/**
 * Point class: represents a point in Dim dimensional space.
 *
 * @author Matt Sachtler
 * @date Spring 2009
 */
template <int Dim>
class Point {
  public:
    Point();

    Point(double arr[Dim]);
    template <typename T>
    explicit Point(T x, ...);
    template <typename T>
    explicit Point(T x0, T x1, T x2);


    Point& operator=(const Point& other);

    /**
     * Gets the value of the Point object in the given dimension
     * (index). This function is const so we don't modify Points using
     * this function.
     *
     * @param index The dimension of the Point to grab.
     * @return The value of the Point in the indexth dimension.
     */
    virtual double operator[](int index) const;

    /**
     * Gets the value of the Point object in the given dimension
     * (index). This is the non-const version, so it can be used to
     * modify Points like so:
     *
     *     Point<3> a(1, 2, 3);
     *     a[0] = 4; // a is now (4, 2, 3)
     *
     * @param index The dimension of the Point to grab.
     * @return The value of the Point in the indexth dimension, by
     *	reference (so that it may be modified).
     */
    virtual double& operator[](int index);

    bool operator==(const Point<Dim> p) const;
    bool operator!=(const Point<Dim> p) const;

    /**
     * Compares whether the given Point is smaller than the current
     * Point.
     *
     * @param p The other point to compare with.
     * @return A boolean value indicating whether the current Point is
     *  smaller than the provided Point p.
     */
    bool operator<(const Point<Dim> p) const;

    bool operator<=(const Point<Dim> p) const;
    bool operator>(const Point<Dim> p) const;
    bool operator>=(const Point<Dim> p) const;

    void set(int index, double val);
    void print(std::ostream& out = std::cout) const;

    bool isMine() const;

  private:
    double vals[Dim];


  //
  // --- Code used for grading if you've visited a node: ---
  //
  public:
    // Pure virtual class for an action when a mine is touched.
    class MineAction {
    public:
      virtual void onMine(const Point<Dim> & point) const = 0;
    };

    // Ctor with a mine value
    Point(double arr[Dim], bool isMine, const MineAction * mineAction);

  private:
    // Default value of a mine is false.
    bool isMine_ = false;

    // Default value of the action is to do nothing.
    class MineAction_DoNothingImpl : public MineAction {
    public:
      void onMine(const Point<Dim> & point) const { }
    };

    MineAction_DoNothingImpl MineAction_DoNothing;
    const MineAction* mineAction_ = &MineAction_DoNothing;

};


template <int Dim>
std::ostream& operator<<(std::ostream& out, const Point<Dim>& p);

#include "point.cpp"

#endif
