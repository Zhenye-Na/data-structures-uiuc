/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++)
    set.push_back(-1);
}

int DisjointSets::find(int elem) {
  if (set[elem] < 0)
    return elem;

  else {
    set[elem] = find(set[elem]);
    return set[elem];
  }
}

void DisjointSets::setunion(int a, int b) {
  a = find(a);
  b = find(b);

  int newSize = set[a] + set[b];

  if (set[a] < set[b]) {
    set[b] = a;
    set[a] = newSize;
  } else {
    set[a] = b;
    set[b] = newSize;
  }
}

int DisjointSets::size(int elem) {
  return -1 * set[find(elem)];
}
