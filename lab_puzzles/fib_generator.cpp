#include "fib.h"

#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;


const string USAGE =
"USAGE: fib [NUM] [OPTIONS]\n"
"Finds the NUMth Fibonacci number.\n"
"\n"
"  -m      Use memoization (defaults to not).\n";

int main(int argc, char* argv[])
{
    unsigned long n = 0;
    bool memoization = false;
    if (argc == 1) {
        cerr << USAGE << endl;
        return -1;
    }

    for (int i = 1; i < argc; i++) {
        /* Are we memoizing? Defaults to no. */
        if (strcmp(argv[i], "-m") == 0) {
            memoization = true;
        } else {
            /* stoi() will except for non-numeric values. */
            try {
                n = stoul(argv[i]);
            } catch (invalid_argument& e) {
                cerr << USAGE << endl;
                return -1;
            } catch (out_of_range& e) {
                cerr << "Number too large to take as input." << endl;
                return -1;
            }
        }
    }
    /* Function pointer points to either the memoized or normal function. */
    unsigned long (*fib_func)(unsigned long);
    fib_func = memoization ? memoized_fib : fib;

    unsigned long previous = 0;
    for (unsigned long i = 0; i <= n; i++) {
        unsigned long result = fib_func(i);
        if (previous <= result) {
            cout << result << endl;
            previous = result;
        } else {
            cout << "Overflowed unsigned long!" << endl;
            break;
        }
    }
}
