/**
 * @file charcount.cpp
 * CharFreq tester program.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "char_counter.h"

#include <iostream>
#include <sstream>
#include <algorithm>

using std::istringstream;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::sort;

template <template <class K, class V> class Dict>
void countCharacters(const string& file, int frequency)
{
    CharFreq<Dict> cf(file);
    vector<pair<char, int>> ret = cf.getChars(frequency);
    sort(ret.begin(), ret.end(),
         [](const pair<char, int>& a, const pair<char, int>& b) -> bool {
             return (a.second == b.second) ? (a.first < b.first)
                                           : (a.second > b.second);
         });
    for (size_t i = 0; i < ret.size(); ++i)
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
    cout << "Finding chars in " << file << " with frequency >= " << arg
         << " using " << htarg << "..." << endl;
    if (htarg == "SCHashTable")
        countCharacters<SCHashTable>(file, arg);
    else
        countCharacters<LPHashTable>(file, arg);
}
