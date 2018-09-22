/**
 * @file char_counter.h
 * Definition of the CharFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
#ifndef _LETTER_COUNTER_H_
#define _LETTER_COUNTER_H_

#include "schashtable.h"
#include "lphashtable.h"
#include "textfile.h"

#include <vector>
#include <string>

/**
 * CharFreq class: a class that allows for counting the frequency with
 * which characters appear in a file.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
template <template <class K, class V> class Dict>
class CharFreq
{
  public:
    /**
     * Constructs a CharFreq object based on the name of a file.
     *
     * @param ifilename Input file to read characters from.
     */
    CharFreq(const std::string& ifilename);

    /**
     * Returns a vector of pairs, where the first element is the
     * character and the second element is the frequency with which the
     * character appeared in the file for the CharFreq object. Only
     * characters with frequency greater than or equal to the
     * threshold are placed in the vector.
     *
     * @param threshold The threshold at which a character, frequency
     *    pair is added to the vector.
     * @return A vector of pairs of characters and frequencies.
     */
    std::vector<std::pair<char, int>> getChars(int threshold);

  private:
    std::string filename; /**< The name of the file to read from. */
};
#include "char_counter.cpp"
#endif
