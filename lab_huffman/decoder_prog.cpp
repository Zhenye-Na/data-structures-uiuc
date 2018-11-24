/**
 * @file decoder_prog.cpp
 * Decoder program for decoding files compressed with HuffmanTrees.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#include "decoder.h"

using namespace std;

int main(int argc, char** argv)
{
    vector<string> args(argv, argv + argc);
    return decoder::main(args);
}
