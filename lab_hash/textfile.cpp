/**
 * @file textfile.cpp
 * Implementation of the TextFile class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
#include "textfile.h"

using std::string;
using std::ifstream;

TextFile::TextFile(const string& filename) : infile(filename.c_str())
{
    /* nothing */
}

TextFile::~TextFile()
{
    if (infile.is_open())
        infile.close();
}

bool TextFile::good()
{
    return infile.good();
}

string TextFile::getNextWord()
{
    string nword = "";
    infile >> nword;

    string bad = ".,!?;:-_[]*/\\'\"`{}()<>&\n\t\r";

    string word = "";
    for (size_t i = 0; i < nword.length(); i++) {
        if (bad.find(nword[i]) == string::npos)
            word += tolower(nword[i]);
    }
    return word;
}
