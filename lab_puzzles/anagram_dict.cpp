/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream temp(filename);
    string word;
    if (temp.is_open()) {
        while (getline(temp, word)) {
            string a = word;
            sort(word.begin(), word.end());
            dict[a].push_back(word);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (auto it = words.begin(); it != words.end(); it++) {
  	    string temp = *it;
  	    sort(temp.begin(), temp.end());
  	    dict[temp].push_back(*it);
  	}
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string key = word;
  	sort(key.begin(), key.end());
  	auto cur = dict.find(key);

  	if (cur == dict.end()) {
  	    return vector <string> ();
  	} else {
  	    auto ret = cur->second;
  	    return ret;
  	}
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> ret;
  	for (auto & it: dict) {
  	    if (it.second.size() > 1) {
  	        ret.push_back(it.second);
  	    }
  	}
  	return ret;
}
