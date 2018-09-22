/**
 * @file lfparse.cpp
 * Logfile Parser application.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "logfile_parser.h"

#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stringstream;

int main(int argc, char** argv)
{
    vector<string> args(argv, argv + argc);
    if (argc < 2) {
        cout << "Usage: " << args[0] << " filename" << endl;
        cout << "\twhere filename is the logfile to be parsed" << endl;
    } else {
        cout << "Parsing logfile: " << args[1] << "..." << endl;
        LogfileParser lfp(args[1]);
        vector<string> urls = lfp.uniquePages();
        cout << "Number of unique URLs: " << urls.size() << endl;
        if (urls.size() > 100) {
            cout << "Too many unique urls, not printing." << endl;
        } else {
            cout << "Printing unique URLs:" << endl;
            for (unsigned int i = 0; i < urls.size(); i++) {
                cout << "\t" << urls[i] << endl;
            }
        }

        cout << "Running sample visited queries..." << endl;

        pair<bool, time_t> ret;
        for (int i = 0; i < 1000; i++) {
            stringstream product;
            product << "/product/" << i << "/";
            if (lfp.hasVisited("chase", product.str())) {
                time_t date = lfp.dateVisited("chase", product.str());
                string t = ctime(&date);
                cout << "\tchase visited " << product.str() << " on " << t;
            }
        }
    }

    return 0;
}
