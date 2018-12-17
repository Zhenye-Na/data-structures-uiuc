/* Your code here! */
#ifndef _DSETS_
#define _DSETS_

#include <algorithm>
#include <vector>

using std::vector;

class DisjointSets {

public:
    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
    int size(int elem);

private:
    vector<int> set;

};

#endif
