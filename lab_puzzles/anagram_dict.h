/**
 * @file anagram_dict.h
 * Definition of a class for finding anagrams of a given word from a word list
 * given at construction.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#ifndef ANAGRAM_DICT_H
#define ANAGRAM_DICT_H

#include <string>
#include <map>
#include <vector>

/**
 * AnagramDict class. Provides interfaces for looking up all anagrams of a
 * given word from a word list (from a file or given vector).
 *
 * @author Matt Joras
 * @date Winter 2013
 */
class AnagramDict
{
  public:
    /**
     * Constructs an AnagramDict from a filename with newline-separated
     * words.
     * @param filename The name of the word list file.
     */
    AnagramDict(const std::string& filename);

    /**
     * Constructs an AnagramDict from a vector of words.
     * @param words The vector of strings to be used as source words.
     */
    AnagramDict(const std::vector<std::string>& words);

    /**
     * @param word The word used to find anagrams.
     * Gets all anagrams of a given word from the dictionary.
     * @return A vector of strings of anagrams of the given word. Empty
     * vector returned if no anagrams are found or the word is not in the
     * word list.
     */
    std::vector<std::string> get_anagrams(const std::string& word) const;

    /**
     * Gets all known anagrams from the dictionary.
     * @return A vector of vectors of strings. Each inner vector contains
     * the "anagram siblings", i.e. words that are anagrams of one another.
     * NOTE: It is impossible to have one of these vectors have less than
     * two elements, i.e. words with no anagrams are ommitted.
     */
    std::vector<std::vector<std::string>> get_all_anagrams() const;

  private:
    std::map<std::string, std::vector<std::string>> dict;
};

#endif /* ANAGRAM_DICT_H */
