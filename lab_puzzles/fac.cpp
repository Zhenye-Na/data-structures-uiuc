/**
 * @file fac.cpp
 * Contains factorial-calculating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fac.h"

#include <iostream>
#include <map>
#include <cstring>
#include <stdexcept>

using namespace std;

const string USAGE =
"USAGE: fac [NUM] [OPTIONS]\n"
"Calculates [NUM]! .\n"
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
                cerr << "Please enter a valid number." << endl;
                return -1;
            } catch (out_of_range& e) {
                cerr << "Number too large to take as input." << endl;
                return -1;
            }
        }
    }
    /* Function pointer points to either the memoized or normal function. */
    unsigned long (*fac_func)(unsigned long);
    fac_func = memoization ? memoized_fac : fac;

    unsigned long previous = 0;
    unsigned long result;
    for (unsigned long i = 0; i <= n; i++) {
        result = fac_func(i);
        if (previous <= result) {
            previous = result;
        } else {
            cout << previous << endl;
            cout << "Overflowed unsigned long!" << endl;
            return -1;
        }
    }
    cout << result << endl;
}

/**
 * Calculates the factorial of the given number.
 * @param n Number to calculate factorial for.
 * @return n!.
 */
unsigned long fac(unsigned long n)
{
    if (n == 0) {
        return 1;
    }
    return n * fac(n - 1);
}

/**
 * Calculates the factorial of the given number.
 * This version utilizes memoization.
 * @param n Number to calculate factorial for.
 * @return n!.
 */
unsigned long memoized_fac(unsigned long n)
{
    /* Fancy initialization of the static map with an initializer list.
     * Maps 0->0, 1->1. */
    static map<unsigned long, unsigned long> memo = {
        {0, 1},
    };

    map<unsigned long, unsigned long>::iterator lookup = memo.find(n);
    if (lookup != memo.end()) {
        return lookup->second;
    } else {
        unsigned long result = n * memoized_fac(n - 1);
        memo[n] = result;
        return result;
    }
}
