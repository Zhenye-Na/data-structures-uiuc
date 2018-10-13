/**
 * @file random.h
 * Random library declarations.
 * Originally written for use with the Graph class to generate random
 *  graphs and integers.
 *
 * @author Sean Massung
 * @date Spring 2011
 */

#ifndef _LAB_GRAPHS_RANDOM_H_
#define _LAB_GRAPHS_RANDOM_H_

#include <vector>

using std::vector;

/**
 * Provides random functionality per a given seed.
 * This is useful when you want predictably random things, like for grading.
 */
class Random
{
  public:
    /**
     * Constructor.
     * @param seed - seed to initialize the RNG
     */
    inline Random(unsigned long seed);

    /**
     * @return a random integer
     */
    inline int nextInt();

    /**
     * Randomly shuffles a vector with the current seed state.
     * @param array - the vector to shuffle
     */
    template <class T>
    void shuffle(vector<T>& array);

  private:
    unsigned long shiftRegister;

    /**
     * @return a random bit
     */
    inline bool LFSR();
};

#include "lab_graphs_random.cpp"
#endif
