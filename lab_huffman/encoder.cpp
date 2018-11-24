/**
 * @file encoder.cpp
 * Implementation of a namespace for encoding files using HuffmanTrees.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <sys/stat.h>

#include "binary_file_writer.h"
#include "encoder.h"
#include "huffman_tree.h"

using namespace std;

int encoder::main(const vector<string>& args)
{
    if (args.size() < 4) {
        printUsage(args[0]);
        return -1;
    }
    encodeFile(args[1], args[2], args[3]);
    return 0;
}

void encoder::printUsage(const string& programName)
{
    cout << "Usage: " << endl;
    cout << "\t" << programName << " input output treefile" << endl;
    cout << "\t\tinput: file to be encoded" << endl;
    cout << "\t\toutput: encoded output" << endl;
    cout << "\t\ttreefile: compressed huffman tree for decoding" << endl;
}

void encoder::encodeFile(const string& inputName, const string& outputName,
                         const string& treeName)
{
    struct stat buf;
    if (0 != stat(inputName.c_str(), &buf)) {
        cerr << "error: input file \"" << inputName << "\" does not exist."
             << endl;
        exit(1);
    }
    ifstream input(inputName);
    stringstream ss;
    ss << input.rdbuf();

    HuffmanTree tree(getFrequencies(ss.str()));
    BinaryFileWriter output(outputName);
    BinaryFileWriter treeFile(treeName);

    cout << "Printing generated HuffmanTree..." << endl;
    tree.print(cout);

    cout << "Saving HuffmanTree to file..." << endl;
    tree.writeToFile(ss.str(), output);
    tree.writeTree(treeFile);
}

vector<Frequency> encoder::getFrequencies(const string& str)
{
    unordered_map<char, int> freqs;
    for (auto it = str.begin(); it != str.end(); ++it)
        freqs[*it]++;
    vector<Frequency> result;
    for (auto it = freqs.begin(); it != freqs.end(); ++it)
        result.push_back(Frequency(it->first, it->second));
    return result;
}
