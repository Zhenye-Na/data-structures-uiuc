/**
 * @file pronounce_dict.h
 * Class that uses the CMU pronunciation dictionary to provide an interface
 * for finding a word's pronunciation.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#ifndef PRONOUNCE_DICT_H
#define PRONOUNCE_DICT_H

#include <string>
#include <map>
#include <vector>

/**
 * PronounceDict class. Provides an interface for finding the pronunciation
 * of a given word based on a pronunciation dictionary provided at
 * construction. Also provides an interface for determining if two word
 * share a pronunciation (they are homophones).
 *
 * @author Matt Joras
 * @date Winter 2013
 */
class PronounceDict
{
  public:
    /**
     * Constructs a PronounceDict from a CMU pronunciation dictionary
     * file. See http://www.speech.cs.cmu.edu/cgi-bin/cmudict .
     * @param pronun_dict_filename Filename of the CMU pronunciation
     * dictionary.
     */
    PronounceDict(const std::string& pronun_dict_filename);

    /**
     * Constructs a PronounceDict from a CMU std::map mapping the word
     * to a vector of strings which represent the pronunciation.
     * @param pronun_dict Maps a string word to a vector of strings
     * representing its pronunciation.
     */
    PronounceDict(
        const std::map<std::string, std::vector<std::string>>& pronun_dict);

    /**
     * Uses the dictionary to determine if the two words are homophones.
     * @param word1 First word to be tested.
     * @param word2 Second word to be tested.
     * @return true if the two words are homophones, false otherwise (or
     * one or both words weren't in the dictionary).
     * Note: The word keys in the dictionary are stored in uppercase.
     */
    bool homophones(const std::string& word1, const std::string& word2) const;

  private:
    std::map<std::string, std::vector<std::string>> dict;
};

#endif /* PRONOUNCE_DICT_H */
