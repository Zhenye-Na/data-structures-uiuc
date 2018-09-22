/**
 * @file wordcount.cpp
 * Testing program for the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
#include "word_counter.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::istringstream;
using std::vector;
using std::sort;

template <template <class K, class V> class Dict>
void countWords(const string& file, int frequency)
{
    WordFreq<Dict> wf(file);
    vector<pair<string, int>> ret = wf.getWords(frequency);
    sort(ret.begin(), ret.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) -> bool {
             return (a.second == b.second) ? (a.first < b.first)
                                           : (a.second > b.second);
         });
    for (unsigned int i = 0; i < ret.size(); i++)
        cout << ret[i].second << "\t" << ret[i].first << endl;
}

void printUsage(const string& progname)
{
    cout << progname << " filename frequency tabletype" << endl;
    cout << "\tfilename: path to the file to count characters in" << endl;
    cout << "\tfrequency: threshold at which a character's frequency must "
            "be to appear in output"
         << endl;
    cout
        << "\ttabletype: type of hash table to use (SCHashTable or LPHashTable)"
        << endl;
}

int main(int argc, char** argv)
{
    vector<string> args(argv, argv + argc);
    if (argc < 4) {
        printUsage(args[0]);
        return 1;
    }
    string file = args[1];
    int arg;
    istringstream iss(args[2]);
    iss >> arg;
    string htarg = args[3];
    std::transform(htarg.begin(), htarg.end(), htarg.begin(), tolower);
    if (htarg.find("sc") == 0)
        htarg = "SCHashTable";
    else
        htarg = "LPHashTable";
    cout << "Finding words in " << file << " with frequency >= " << arg
         << " using " << htarg << "..." << endl;
    if (htarg == "SCHashTable")
        countWords<SCHashTable>(file, arg);
    else
        countWords<LPHashTable>(file, arg);
}
