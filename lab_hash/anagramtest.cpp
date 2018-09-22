/**
 * @file anagramtest.cpp
 * Test for the anagram finder.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "anagram_finder.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::string;

template <template <class K, class V> class Dict>
void findAnagrams(const string& filename, const string& testword)
{
    AnagramFinder<Dict> fileFinder(filename);
    fileFinder.writeAnagrams(testword, "anagrams.txt");
    vector<string> anagrams = fileFinder.getAnagrams(testword);

    for (unsigned int i = 0; i < anagrams.size(); i++)
        cout << anagrams[i] << " is an anagram of " << testword << endl;
}

int main(int argc, char** argv)
{
    if (argc < 4) {
        cout << "Testing with a dumb example..." << endl;
        vector<string> strings;
        strings.push_back("igloo");
        strings.push_back("oolgi");
        strings.push_back("glooi");
        strings.push_back("dog");
        strings.push_back("cat");
        strings.push_back("iglo");

        cout << "finding anagrams..." << endl;
        AnagramFinder<SCHashTable> finder(strings);
        vector<string> anagrams = finder.getAnagrams("igloo");

        for (unsigned int i = 0; i < anagrams.size(); i++)
            cout << anagrams[i] << " is an anagram of igloo" << endl;
    } else {
        vector<string> args(argv, argv + argc);
        string htarg = args[3];
        std::transform(htarg.begin(), htarg.end(), htarg.begin(), tolower);
        if (htarg.find("sc") == 0)
            htarg = "SCHashTable";
        else
            htarg = "LPHashTable";
        cout << "Checking file " << args[1] << " for anagrams of " << args[2]
             << " using " << htarg << "..." << endl;
        if (htarg == "SCHashTable")
            findAnagrams<SCHashTable>(args[1], args[2]);
        else
            findAnagrams<LPHashTable>(args[1], args[2]);
    }
    return 0;
}
