/**
 * @file decoder.cpp
 * Implementation of a namespace for decoding files using HuffmanTrees.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sys/stat.h>

#include "binary_file_reader.h"
#include "decoder.h"
#include "huffman_tree.h"

using namespace std;

int decoder::main(const vector<string>& args)
{
    if (args.size() < 4) {
        printUsage(args[0]);
        return -1;
    }
    decodeFile(args[1], args[2], args[3]);
    return 0;
}

void decoder::printUsage(const string& programName)
{
    cout << "Usage: " << endl;
    cout << "\t" << programName << " input treefile output" << endl;
    cout << "\t\tinput: file to be decoded" << endl;
    cout << "\t\ttreefile: compressed huffman tree to use for decoding" << endl;
    cout << "\t\toutput: decompressed file" << endl;
}

void decoder::decodeFile(const string& inputName, const string& treeName,
                         const string& outputName)
{
    struct stat buf;
    if (0 != stat(inputName.c_str(), &buf)) {
        cerr << "error: input file \"" << inputName << "\" does not exist."
             << endl;
        exit(1);
    }
    if (0 != stat(treeName.c_str(), &buf)) {
        cerr << "error: tree file \"" << treeName << "\" does not exist."
             << endl;
        exit(1);
    }
    BinaryFileReader input(inputName);
    BinaryFileReader treeIn(treeName);
    HuffmanTree tree(treeIn);

    ofstream output(outputName);
    output << tree.decodeFile(input);
}
