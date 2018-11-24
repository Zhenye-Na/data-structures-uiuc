/**
 * @file print_as_ascii.cpp
 * A simple command line program that prints a binary file (as created from
 * a BinaryFileWriter) as a sequence of ascii 0s and 1s.
 */

#include <iostream>
#include <string>
#include <vector>

#include "binary_file_reader.h"

void print_usage(const std::string& name)
{
    std::cout
        << "Usage: " << name << " filename"
        << "\n\tPrints filename (a binary file) to standard out as a sequence"
           " of ASCII 0s and 1s."
        << std::endl;
}

void print_as_ascii(const std::string& filename)
{
    BinaryFileReader file(filename);
    while (file.hasBits())
        std::cout << file.getNextBit();
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    std::vector<std::string> args(argv, argv + argc);
    if (args.size() < 2) {
        print_usage(args[0]);
        return 1;
    }
    print_as_ascii(args[1]);
    return 0;
}
