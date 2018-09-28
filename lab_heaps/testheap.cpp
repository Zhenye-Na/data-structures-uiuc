/**
 * @file testheap.cpp
 * Heap Testing Code
 *
 * @author Jack Toole
 * @date Fall 2011
 *
 * @author Chase Geigle
 * @date Fall 2012
 */

#include <iostream>
#include <fstream>
#include <ctype.h>
#include <time.h>
#include <utility>
#include "coloredout.h"
#include "heap.h"
#include "random.h"

using namespace std;
using namespace util;

void testConstructor(int count);
void testPop(int count);
void testPush(int count);

void printHeader(const string& headline)
{
    cout << string(64, colored_out::BORDER_CHAR) << endl;
    colored_out::output_bold(headline);
    cout << endl << string(64, colored_out::BORDER_CHAR) << endl;
}

void printAfter(int value, std::string operation = "remove")
{
    cout << endl;
    colored_out::output_bold("After " + operation + "(");
    colored_out::output_bold(value);
    colored_out::output_bold(")");
    cout << endl;
}

int main(int argc, const char** argv)
{
    // Set up Colored Output (if 'color' parameter passed)
    bool is_colored
        = (argc > 1 && tolower(argv[1][0]) == 'c') && isatty(STDOUT_FILENO);
    colored_out coloroutput;
    if (is_colored) {
        coloroutput.set_expected_file("soln_testheap.out");
        int status = coloroutput.start();
        if (status < 0)
            return 0;
    }

    // Read command line 'count' - number of things to put in our
    int count = 15;
    if (argc > 1 && !is_colored) {
        stringstream arg(argv[1]);
        arg >> count;
    }

    testConstructor(count);
    testPush(count);
    testPop(count);

    return 0;
}

vector<int> setUpVector(int seed, int count)
{
    Random rand_gen(seed);
    vector<int> result;
    result.reserve(seed);
    for (int i = 0; i < count; i++)
        result.push_back(i);
    random_shuffle(result.begin(), result.end(), rand_gen);
    return result;
}

void testPush(int count)
{
    vector<int> to_insert = setUpVector(67, count);
    printHeader("Testing push:");
    heap<int> myHeap;
    for (size_t i = 0; i < to_insert.size(); ++i) {
        myHeap.push(to_insert[i]);
        printAfter(to_insert[i], "push");
        cout << myHeap;
    }
}

void testPop(int count)
{
    printHeader("Testing pop (requires constructor to be working):");
    vector<int> to_insert = setUpVector(67, count);
    heap<int> myHeap(to_insert);
    cout << "Original Heap:" << endl;
    cout << myHeap;

    bool passed = true;
    for (int i = 0; i < (int)to_insert.size(); i++) {
        if (myHeap.empty()) {
            colored_out::output_bold("Incorrect: Heap should not be empty yet");
            cout << endl;
            passed = false;
            break;
        }
        int min = myHeap.pop();

        if (count < 64 || i != min) {
            printAfter(min, "pop");
            cout << myHeap;
        }
        if (i != min) {
            colored_out::output_bold("Incorrect: pop returned ");
            colored_out::output_bold(min);
            colored_out::output_bold(", but it should have returned ");
            colored_out::output_bold(i);
            cout << endl;
            passed = false;
            break;
        }
    }

    if (passed) {
        if (myHeap.empty())
            colored_out::output_bold("Pop Passed!");
        else
            colored_out::output_bold("Incorrect: Heap should be empty now");
        cout << endl;
    }
    cout << endl;
}

void testConstructor(int count)
{
    Random rand_gen(92);
    vector<int> myArray;
    myArray.reserve(count);

    for (int i = 0; i < count; i++)
        myArray.push_back(i);
    random_shuffle(myArray.begin(), myArray.end(), rand_gen);

    printHeader("Testing Constructor");
    cout << colored_out::BORDER_CHAR
         << " Original array: " << colored_out::BORDER_CHAR << endl;
    cout << "[";
    for (size_t i = 0; i < myArray.size(); ++i)
        cout << " " << myArray[i];
    cout << " ]" << endl << endl;

    cout << colored_out::BORDER_CHAR
         << " After buildheap: " << colored_out::BORDER_CHAR << endl;

    heap<int> myHeap(myArray);
    cout << myHeap;
    cout << endl << endl;
}

/**
 *  This test is NEVER RUN, but ONLY COMPILED.
 *   Its compilation checks that you aren't using any values, i.e.
 *   array[i], as an index into the array (since a string can't be
 *   used as an index into an array. If you do, this code will
 *   prevent the heap code from compiling. Neat, huh?
 **/
void testCompileOnly()
{
    vector<string> testHeapStringsCompiles;
    heap<string> myHeap(testHeapStringsCompiles);
    myHeap.pop();
}
