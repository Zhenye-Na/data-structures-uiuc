/**
 * @file no_sort.h
 * Masks std sorting algorithms with error messages to prevent students from
 *  using the STL's sorting functions.
 * @author Sean Massung
 * @date Summer 2012
 */

#ifndef _NO_SORT_H_
#define _NO_SORT_H_

#include <algorithm>
#include <iostream>
#include <vector>

// included specifically for MP6
#include "../point.h"

using std::endl;
using std::cerr;
using std::vector;

#define NOPE(X)                                                                \
    template <>                                                                \
    inline void sort(vector<X>::iterator left, vector<X>::iterator right)      \
    {                                                                          \
        left, right;                                                           \
        cerr << "ERROR: std::sort not permitted" << endl;                      \
    }                                                                          \
    template <class C>                                                         \
    inline void sort(vector<X>::iterator left, vector<X>::iterator right,      \
                     C comp)                                                   \
    {                                                                          \
        left, right, comp;                                                     \
        cerr << "ERROR: std::sort not permitted" << endl;                      \
    }                                                                          \
    template <>                                                                \
    inline void sort_heap(vector<X>::iterator left, vector<X>::iterator right) \
    {                                                                          \
        left, right;                                                           \
        cerr << "ERROR: std::sort_heap not permitted" << endl;                 \
    }                                                                          \
    template <class C>                                                         \
    inline void sort_heap(vector<X>::iterator left, vector<X>::iterator right, \
                          C comp)                                              \
    {                                                                          \
        left, right, comp;                                                     \
        cerr << "ERROR: std::sort_heap not permitted" << endl;                 \
    }                                                                          \
    template <>                                                                \
    inline void stable_sort(vector<X>::iterator left,                          \
                            vector<X>::iterator right)                         \
    {                                                                          \
        left, right;                                                           \
        cerr << "ERROR: std::stable_sort not permitted" << endl;               \
    }                                                                          \
    template <class C>                                                         \
    inline void stable_sort(vector<X>::iterator left,                          \
                            vector<X>::iterator right, C comp)                 \
    {                                                                          \
        left, right, comp;                                                     \
        cerr << "ERROR: std::stable_sort not permitted" << endl;               \
    }                                                                          \
    template <class C>                                                         \
    inline vector<X>::iterator partition(vector<X>::iterator left,             \
                                         vector<X>::iterator right, C comp)    \
    {                                                                          \
        left, right, comp;                                                     \
        cerr << "ERROR: std::partition not permitted" << endl;                 \
        return left;                                                           \
    }                                                                          \
    template <class C>                                                         \
    inline vector<X>::iterator stable_partition(                               \
        vector<X>::iterator left, vector<X>::iterator right, C comp)           \
    {                                                                          \
        left, right, comp;                                                     \
        cerr << "ERROR: std::stable_partition not permitted" << endl;          \
        return left;                                                           \
    }                                                                          \
    template <class C>                                                         \
    inline void nth_element(vector<X>::iterator left,                          \
                            vector<X>::iterator right)                         \
    {                                                                          \
        left, right;                                                           \
        cerr << "ERROR: std::nth_element not permitted" << endl;               \
    }                                                                          \
    template <class C>                                                         \
    inline void nth_element(vector<X>::iterator left,                          \
                            vector<X>::iterator right, C comp)                 \
    {                                                                          \
        left, right, comp;                                                     \
        cerr << "ERROR: std::nth_element not permitted" << endl;               \
    }                                                                          \
    template <class C>                                                         \
    inline void partial_sort(vector<X>::iterator left,                         \
                             vector<X>::iterator right)                        \
    {                                                                          \
        left, right;                                                           \
        cerr << "ERROR: std::partial_sort not permitted" << endl;              \
    }                                                                          \
    template <class C>                                                         \
    inline void partial_sort(vector<X>::iterator left,                         \
                             vector<X>::iterator right, C comp)                \
    {                                                                          \
        left, right, comp;                                                     \
        cerr << "ERROR: std::partial_sort not permitted" << endl;              \
    }

namespace std
{
    NOPE(int)
    NOPE(unsigned int)
    NOPE(bool)
    NOPE(char)
    NOPE(unsigned char)
    NOPE(signed char)
    NOPE(double)
    NOPE(long double)
    NOPE(long)
    NOPE(long long)
    NOPE(unsigned long)
    NOPE(unsigned long long)
    NOPE(float)
    NOPE(short)
    NOPE(unsigned short)
    NOPE(Point<1>)
    NOPE(Point<2>)
    NOPE(Point<3>)
    NOPE(Point<4>)
    NOPE(Point<5>)
}

#endif
