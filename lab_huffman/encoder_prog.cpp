/**
 * Program for encoding files with HuffmanTrees.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#include "encoder.h"

using namespace std;

int main(int argc, char** argv)
{
    vector<string> args(argv, argv + argc);
    return encoder::main(args);
}
