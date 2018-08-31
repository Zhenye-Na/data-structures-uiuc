#ifndef CS225_CATCHLIB
#define CS225_CATCHLIB


#define CATCH_CONFIG_ENABLE_ALL_STRINGMAKERS    // we want pretty output
#include "catch.hpp"


#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <utility>
#include <algorithm>
#include <unistd.h>


// put (generic) custom string formatters here
// https://github.com/catchorg/Catch2/blob/v2.0.1/docs/tostring.md#catchstringmaker-specialisation
namespace Catch
{
}

namespace cs225
{
/**
 * Returns whether the given filename exists.
 * Note that most assignments change into the tests directory.
 */
bool fileExists(std::string fileName);

/**
 * Prints a warning to run the test cases in valgrind
 */
void print_valgrind();

/**
 * Print a random quote from the file filename.
 *
 * @param filename The path to the quotes file
 */
void print_quote(std::string filename);

};


#endif
