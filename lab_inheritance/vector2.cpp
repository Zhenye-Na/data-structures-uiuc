/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 *
 * Please see vector2.h for documentation of the Vector2 class
 */

#include "vector2.h"

#include <cmath>

Vector2::Vector2() : x_(0), y_(0)
{
    /* Nothing.  See initialization list */
}

Vector2::Vector2(double px, double py) : x_(px), y_(py)
{
    /* Nothing.  See initialization list */
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(this->x_ - other.x_, this->y_ - other.y_);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(this->x_ + other.x_, this->y_ + other.y_);
}

Vector2 Vector2::operator*(int constant)
{
    return Vector2(this->x_ * constant, this->y_ * constant);
}

Vector2 Vector2::operator/(int constant)
{
    return Vector2(this->x_ / constant, this->y_ / constant);
}

Vector2 Vector2::leftHandNormal() const
{
    return Vector2(this->y_, -1 * this->x_);
}

Vector2 Vector2::rightHandNormal() const
{
    return Vector2(-1 * this->y_, this->x_);
}

double Vector2::distanceTo(const Vector2& other) const
{
    const double delta_x = this->x() - other.x();
    const double delta_y = this->y() - other.y();
    const double distanceSquared = (delta_x * delta_x) + (delta_y * delta_y);
    const double distance = sqrt(distanceSquared);
    return distance;
}

double Vector2::dotProduct(const Vector2& other) const
{
    const double dot_product
        = ((this->x() * other.x()) + (this->y() * other.y()));
    return dot_product;
}

double Vector2::crossProduct(const Vector2& other) const
{
    return (this->x() * other.y()) - (this->y() * other.x());
}

Vector2 Vector2::projectionOn(const Vector2& b) const
{
    const double dot_product = this->dotProduct(b);
    const double tlength2 = b.length2();
    const double temp = dot_product / tlength2;
    return Vector2(temp * b.x(), temp * b.y());
}

double Vector2::length2() const
{
    return (this->x_ * this->x_) + (this->y_ * this->y_);
}

double Vector2::length() const
{
    return sqrt(this->length2());
}

double Vector2::magnitude() const
{
    return this->length();
}

Vector2 Vector2::normalize() const
{
    const double tlength = this->length();
    Vector2 tnormalize;
    if (tlength > 0) {
        tnormalize.set_x(this->x() / tlength);
        tnormalize.set_y(this->y() / tlength);
    }
    return tnormalize;
}

bool Vector2::operator==(const Vector2& other) const
{
    return (this->x_ == other.x_) && (this->y_ == other.y_);
}

double Vector2::x() const
{
    return this->x_;
}

void Vector2::set_x(double px)
{
    this->x_ = px;
}

double Vector2::y() const
{
    return this->y_;
}

void Vector2::set_y(double py)
{
    this->y_ = py;
}

bool Vector2::isNorthOf(const Vector2& other) const
{
    return this->y() < other.y();
}

bool Vector2::isNorthWestOf(const Vector2& other) const
{
    return this->isNorthOf(other) && this->isWestOf(other);
}

bool Vector2::isNorthEastOf(const Vector2& other) const
{
    return this->isNorthOf(other) && this->isEastOf(other);
}

bool Vector2::isSouthOf(const Vector2& other) const
{
    return this->y() > other.y();
}

bool Vector2::isSouthWestOf(const Vector2& other) const
{
    return this->isSouthOf(other) && this->isWestOf(other);
}

bool Vector2::isSouthEastOf(const Vector2& other) const
{
    return this->isSouthOf(other) && this->isEastOf(other);
}

bool Vector2::isWestOf(const Vector2& other) const
{
    return this->x() < other.x();
}

bool Vector2::isEastOf(const Vector2& other) const
{
    return this->x() > other.x();
}
