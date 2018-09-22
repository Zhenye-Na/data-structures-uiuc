/**
 * @file char_counter.cpp
 * Implementation of the CharFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

using std::vector;
using std::string;
using std::pair;

/**
 * Constructs a CharFreq object based on the name of a file.
 *
 * @param ifilename Input file to read characters from.
 */
template <template <class K, class V> class Dict>
CharFreq<Dict>::CharFreq(const string& ifilename)
    : filename(ifilename)
{
    /* nothing */
}

/**
 * Returns a vector of pairs, where the first element is the character and
 * the second element is the frequency with which the character appeared in
 * the file for the CharFreq object. Only characters with frequency greater
 * than or equal to the threshold are placed in the vector.
 *
 * @param threshold The threshold at which a character, frequency pair is
 *    added to the vector.
 * @return A vector of pairs of characters and frequencies.
 */
template <template <class K, class V> class Dict>
vector<pair<char, int>> CharFreq<Dict>::getChars(int threshold)
{
    TextFile infile(filename);
    Dict<char, int> hashTable(256);
    while (infile.good()) {
        string word = infile.getNextWord();
        for (size_t i = 0; i < word.length(); i++)
            hashTable[word[i]]++;
    }
    vector<pair<char, int>> ret;
    // we iterate over the hash tables using iterators: it->first will give
    // us the key, it->second will give us the value. it++ moves to the
    // next (key, value) pair in the HashTable.
    typename Dict<char, int>::iterator it;
    for (it = hashTable.begin(); it != hashTable.end(); it++) {
        if (it->second >= threshold)
            ret.push_back(*it);
    }
    return ret;
}
