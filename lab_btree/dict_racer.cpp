#include "btree.h"
#include "benchmark.h"

#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <ctime>
#include <stdexcept>
#include <sstream>

using namespace std;

void run_benchmark(unsigned int n, unsigned int step, unsigned int order,
                   bool inserts, bool finds, bool rand);

bool stob(const string& s)
{
    string temp = s;
    transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
    return temp == "1" || temp == "TRUE";
}

const string USAGE =
"USAGE: dict_racer ORDER N STEP RANDOM INSERTS FINDS\n"
"Runs a race between a BTree< int, int > of order ORDER against an \n"
"std::map< int, int > for N inserts / finds. Outputs CSVs into \"results\".\n"
"ORDER specifies the order of the BTree\n"
"N specifies the max number of insert / finds to do\n"
"STEP specifies the intervals to split N into. E.g. N = 10, STEP = 2 will make\n"
"points for 2 operations, 4 operations ... &c.\n"
"RANDOM specifies whether the data should be random or sequential.\n"
"INSERT specifies whether to benchmark the inserts.\n"
"FINDS specifies whether to benchmark the finds.\n\n"
"Results can be plotted with the simple python script generate_plot.py, e.g.\n"
"./generate_plot.py results/*.csv\n";


int main(int argc, char* argv[])
{
    if (argc != 7) {
        cout << USAGE << endl;
        return -1;
    } else {
        try {
            int order = stoi(argv[1]);
            int n = stoi(argv[2]);
            int step = stoi(argv[3]);
            bool random = stob(argv[4]);
            bool inserts = stob(argv[5]);
            bool finds = stob(argv[6]);
            if (!inserts && !finds) {
                cout << "Please specify whether to do inserts / finds." << endl;
            } else {
                run_benchmark(n, step, order, inserts, finds, random);
            }
        } catch (invalid_argument& e) {
            cout << USAGE << endl;
            return -1;
        } catch (out_of_range& e) {
            cout << "Number too large to take as input." << endl;
            return -1;
        }
    }
}

/* TODO Make this generic so that the awful code repetition doesn't have to
 * happen. */
void run_benchmark(unsigned int n, unsigned int step, unsigned int order,
                   bool inserts, bool finds, bool random)
{
    if (!inserts && !finds)
        return;

    vector<int> data;
    data.reserve(n);

    stringstream bt_benchmark_name;
    stringstream mp_benchmark_name;
    bt_benchmark_name << "BTree(" << order << ")<int,int>_" << n << "_";
    mp_benchmark_name << "std::map<int,int>_" << n << "_";
    if (inserts && finds) {
        bt_benchmark_name << "inserts, finds_";
        mp_benchmark_name << "inserts, finds_";
    } else if (finds) {
        bt_benchmark_name << "finds_";
        mp_benchmark_name << "finds_";
    } else {
        bt_benchmark_name << "inserts_";
        mp_benchmark_name << "inserts_";
    }

    if (random) {
        srand(time(NULL));
        for (unsigned int i = 0; i < n; i++) {
            int rand_val = rand();
            data.push_back(rand_val);
        }
        bt_benchmark_name << "random";
        mp_benchmark_name << "random";
    } else {
        for (unsigned int i = 0; i < n; i++) {
            data.push_back(i);
        }
        bt_benchmark_name << "sequential";
        mp_benchmark_name << "sequential";
    }

    BTree<int, int> bt(order);
    map<int, int> mp;
    Benchmark b("blah");
    Benchmark bt_b(bt_benchmark_name.str());
    Benchmark mp_b(mp_benchmark_name.str());

    for (unsigned int i = 0; i < n; i += step) {
        size_t curr = bt_b.add_point(i);
        if (inserts) {
            bt_b.start(curr);
        }
        for (unsigned int j = 0; j < i; j++) {
            bt.insert(data[j], data[j]);
        }

        if (finds) {
            if (!inserts) {
                bt_b.start(curr);
            }
            for (unsigned int j = 0; j < i; j++) {
                int val = bt.find(data[j]);
                if (val != data[j]) {
                    cout << data[j] << " " << j << endl;
                }
            }
        }
        bt_b.end(curr);
        bt.clear();
    }
    bt_b.write_to_file();

    for (unsigned int i = 0; i < n; i += step) {
        size_t curr = mp_b.add_point(i);
        if (inserts) {
            mp_b.start(curr);
        }
        for (unsigned int j = 0; j < i; j++) {
            mp.insert(make_pair(data[j], data[j]));
        }

        if (finds) {
            if (!inserts) {
                mp_b.start(curr);
            }
            for (unsigned int j = 0; j < i; j++) {
                int val = mp[data[j]];
                if (val != data[j]) {
                    cout << data[j] << " " << j << endl;
                }
            }
        }
        mp_b.end(curr);
        mp.clear();
    }
    mp_b.write_to_file();
}
