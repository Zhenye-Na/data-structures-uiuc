/**
 * @file common_words.h
 * Header file of a class to find all the common words across multiple files
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#ifndef COMMON_WORDS_H
#define COMMON_WORDS_H

#include <string>
#include <map>
#include <vector>

using std::map;
using std::vector;
using std::string;

/**
 * CommonWords class. Definition of a class to find all the common words across
 * multiple files
 *
 * @author Zach Widder
 * @date October 2014
 */
class CommonWords
{
  public:
    /**
     * Constructs a CommonWords object from a vector of filenames.
     * @param filenames The list of filenames to read.
     */
    CommonWords(const std::vector<std::string>& filenames);

    /**
     * @param n The number of times to word has to appear.
     * @return A vector of strings. The vector contains all words that appear
     * in each file >= n times.
     */
    std::vector<std::string> get_common_words(unsigned int n) const;

  private:
    /**
     * #file_word_maps holds a map for each file. Each map associates a word in
     * that file to the number of times it has been seen in that file.
     */
    vector<map<string, unsigned int>> file_word_maps;

    /**
     * #common maps a word to the number of documents that word appears in
     */
    std::map<std::string, unsigned int> common;

    /* helper functions */

    /**
     * Initializes #file_word_maps.
     * @param filenames The vector of names of the files that will be used
     */
    void init_file_word_maps(const vector<string>& filenames);

    /**
     * Initializes #common.
     */
    void init_common();

    /**
     * Takes a filename and transforms it to a vector of all words in that file.
     * @param filename The name of the file that will fill the vector
     */
    vector<string> file_to_vector(const string& filename) const;
};

#endif
