/**
 * @file logfile_generator.cpp
 * Logfile Generator application.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include <stdlib.h>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ofstream;
using std::stringstream;
using std::istringstream;

#define ONE_DAY 60 * 60 * 24

int main(int argc, char** argv)
{
    vector<string> args(argv, argv + argc);
    if (argc < 4) {
        cout << "Usage: " << args[0] << " filename products lines" << endl;
        cout << "\tfilename: output for log file" << endl;
        cout << "\tproducts: number of unique products" << endl;
        cout << "\tlines:    number of lines to generate" << endl;
    } else {
        int products = 0;
        istringstream issp(args[2]);
        issp >> products;
        int lines = 0;
        istringstream iss(args[3]);
        iss >> lines;

        vector<string> customers;

        // prof
        customers.push_back("cinda");

        // grad staff
        customers.push_back("sandro");
        customers.push_back("simon");
        customers.push_back("harshitha");
        customers.push_back("shreyas");
        customers.push_back("nadia");
        customers.push_back("rui");

        // undergrads
        customers.push_back("bill");
        customers.push_back("dave");
        customers.push_back("chase");
        customers.push_back("dan");
        customers.push_back("kyle");
        customers.push_back("alex_k");
        customers.push_back("alex_l");
        customers.push_back("hongda");
        customers.push_back("sean");
        customers.push_back("andy");
        customers.push_back("will");
        customers.push_back("arjan");
        customers.push_back("jack");

        ofstream out(args[1].c_str());

        time_t date = time(NULL);
        srand(date);
        for (int i = 0; i < lines; i++) {
            int cidx = rand() % customers.size();
            stringstream line;
            line << "[" << customers[cidx] << "]:\t";

            int pidx = rand() % products;
            line << "/product/" << pidx << "/\t";

            time_t ndate = date - (rand() % 5) * ONE_DAY - rand() % 10000;
            char buff[100]; // totally arbitrary...
            tm* time = localtime(&ndate);
            time->tm_isdst = 1; // UGLY!
            strftime(buff, 100, "%c", time);
            line << buff;
            out << line.str() << endl;
        }
        out.close();
    }
    return 0;
}
