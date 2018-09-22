/**
 * @file anagram_finder.h
 * Definition of an AnagramFinder class for finding anagrams in a set of
 * strings or within a file.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#ifndef _ANAGRAM_FINDER_H_
#define _ANAGRAM_FINDER_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "schashtable.h"
#include "lphashtable.h"
#include "textfile.h"

/**
 * AnagramFinder class. Provides an interface for finding anagrams in a set
 * of strings or within a file.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
template <template <class K, class V> class Dict>
class AnagramFinder
{
  public:
    /**
     * Constructs an AnagramFinder based on a filename to read
     * potential anagrams from.
     *
     * @param ifilename The name of the file to read in.
     */
    AnagramFinder(const std::string& ifilename);

    /**
     * Constructs an AnagramFinder based on a set of strings instead of
     * a filename.
     *
     * @param istrings The set of strings to use for this finder.
     */
    AnagramFinder(const std::vector<std::string>& istrings);

    /**
     * Retrieves a set of words that are anagrams of a given word.
     *
     * @param word The word we wish to find anagrams of inside the
     *    finder.
     */
    std::vector<std::string> getAnagrams(const std::string& word);

    /**
     * Retrieves a set of anagrams in the finder of a given words, but
     * writes them out to a file instead of returning a vector.
     *
     * @param word The word we wish to find anagrams of inside the
     *    finder.
     * @param output_file The name of the file we want to write to.
     */
    void writeAnagrams(const std::string& word, const std::string& output_file);

  private:
    // indicates where to read data from
    bool file; /**< Indicates whether a file was used to build the
                    finder or not. */

    std::string filename; /**< Name of the file to read anagrams from. Only
                            set if the file-based constructor is used. */
    std::vector<std::string> strings; /**< Set of strings to find
                                        anagrams in. Only set if the
                                        std::vector constructor is
                                        used. */

    /**
     * Determines if the given word is an anagram of the test word.
     *
     * @param word Word that is possibly an anagram.
     * @param test Word to check against.
     * @return A boolean value indicating whether word is an anagram of
     *    test.
     */
    bool checkWord(const std::string& word, const std::string& test);
};
#include "anagram_finder.cpp"
#endif
