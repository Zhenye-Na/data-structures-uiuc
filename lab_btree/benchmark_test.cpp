#include "benchmark.h"
#include <map>

using namespace std;

int main()
{
    Benchmark test("test");
    map<int, int> m;

    size_t curr = test.add_point(10000);
    test.start(curr);
    for (int i = 0; i < 10000; i++) {
        m[i] = i;
    }
    for (int i = 0; i < 10000; i++) {
        m.find(i);
    }
    test.end(curr);

    m.clear();
    curr = test.add_point(100000);
    test.start(curr);
    for (int i = 0; i < 100000; i++) {
        m[i] = i;
    }
    for (int i = 0; i < 100000; i++) {
        m.find(i);
    }
    test.end(curr);

    m.clear();
    curr = test.add_point(1000000);
    test.start(curr);
    for (int i = 0; i < 1000000; i++) {
        m[i] = i;
    }
    for (int i = 0; i < 1000000; i++) {
        m.find(i);
    }
    test.end(curr);

    test.write_to_file();
}
