#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../heap.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <time.h>
#include <utility>

#include "catchlib.h"
#include "../random.h"

using namespace std;

void helpTestHeapifyDown(const vector<int> & vals)
{
    heap<int> herp;
    for(size_t i = 0; i < vals.size(); ++i)
        herp.push(vals[i]);

    vector<int> sorted = vals;
    sort(sorted.begin(), sorted.end());

    for(size_t i = 0; i < sorted.size(); i++)
        REQUIRE(sorted[i] == herp.pop());
}

TEST_CASE("test_heapify_down_1", "[weight=1]")
{
    vector<int> vals = {6, 7, 8};
    helpTestHeapifyDown(vals);
}

TEST_CASE("test_heapify_down_2", "[weight=1]")
{
    vector<int> vals = {99, 7, 12, 945, 8, 1234};
    helpTestHeapifyDown(vals);
}

TEST_CASE("test_heapify_down_3", "[weight=1]")
{
    vector<int> vals = {30, 39, 69, 52, 64, 94, 98, 21, 25, 87, 1};
    helpTestHeapifyDown(vals);
}

TEST_CASE("test_heapify_down_4", "[weight=1]")
{
    vector<int> vals = {47, 36, 76, 40, 14, 100, 23, 56, 35, 62, 6, 16, 90, 37, 18};
    helpTestHeapifyDown(vals);
}

TEST_CASE("test_heapify_down_5", "[weight=1]")
{
    vector<int> vals = {16, 66, 7, 55, 29, 84, 64, 74, 82, 53, 10, 68, 62, 9,
            46, 67, 39, 25, 78, 48, 76, 19, 89, 22, 49, 83, 99, 45, 88, 28, 73,
            84, 7, 4, 30, 83, 48, 79, 54, 24, 92, 44, 97, 24, 46, 78, 28, 56,
            6, 74, 37, 82, 21, 71, 93, 74, 45, 15, 69, 35, 41, 85, 86, 62, 52, 71};
    helpTestHeapifyDown(vals);
}

TEST_CASE("test_build_heap_1", "[weight=1]")
{
	vector<int> vals = {3, 2, 1};
	heap<int> myHeap(vals);
	vector<int> test;
	myHeap.getElems(test);
	vector<int> expected = {1, 2, 3};
	bool matches = (test == expected);
	REQUIRE(matches == true);
}

TEST_CASE("test_build_heap_2", "[weight=1]")
{
	vector<int> vals = {5, 7, 2, 9, 8, 1};
	heap<int> myHeap(vals);
	vector<int> test;
	myHeap.getElems(test);
	vector<int> expected1 = {1,7,2,9,8,5};
	vector<int> expected2 = {1,2,5,8,7,9};
	bool matches = (test == expected1) || (test == expected2);
	REQUIRE(matches == true);
}

TEST_CASE("test_build_heap_3", "[weight=1]")
{
	vector<int> vals = {30, 39, 69, 11, 52, 64, 94, 98, 21, 25, 87, 1, 83};
	heap<int> myHeap(vals);
	vector<int> test;
	myHeap.getElems(test);
	vector<int> expected1 = {1,11,30,21,25,64,94,98,39,52,87,69,83};
	vector<int> expected2 = {1,21,11,25,64,30,98,52,39,87,69,83,94};
	bool matches = (test == expected1) || (test == expected2);
	REQUIRE(matches == true);
}

TEST_CASE("test_build_heap_4", "[weight=1]")
{
	vector<int> vals = {47, 36, 76, 40, 14, 100, 23, 56, 70, 71, 35, 62, 6, 16, 90, 37, 18};
	heap<int> myHeap(vals);
	vector<int> test;
	myHeap.getElems(test);
	vector<int> expected1 = {6,14,16,18,35,62,23,37,70,71,36,76,100,47,90,40,56};
	vector<int> expected2 = {6,14,16,18,35,23,37,47,71,100,62,36,40,90,56,70,76};
	bool matches = (test == expected1) || (test == expected2);
	REQUIRE(matches == true);
}

TEST_CASE("test_build_heap_5", "[weight=1]")
{
	vector<int> vals = {16, 66, 7, 55, 29, 84, 64, 74, 82, 53, 10, 68, 62, 9,
            46, 67, 39, 25, 78, 48, 76, 19, 89, 22, 49, 83, 99, 45, 88, 28, 73,
            84, 7, 4, 30, 83, 48, 79, 54, 24, 92, 44, 97, 24, 46, 78, 28, 56,
            6, 74, 37, 82, 21, 71, 93, 74, 45, 15, 69, 35, 41, 85, 86, 62, 52, 71};
	heap<int> myHeap(vals);
	vector<int> test;
	myHeap.getElems(test);
	vector<int> expected1 = {4,7,6,16,10,7,9,30,25,24,19,22,21,15,28,52,39,48,54,48,44,24,28,56,37,62,71,45,64,35,73,55,67,66,74,83,82,79,78,53,92,76,97,29,46,78,89,84,68,74,49,82,83,99,93,74,45,88,69,46,41,85,86,62,84,71};
	vector<int> expected2 = {4,7,6,7,10,9,15,16,24,19,22,37,21,28,41,29,25,48,48,44,24,46,28,49,64,55,45,45,35,67,62,52,39,30,83,78,79,54,53,92,76,97,84,89,78,68,56,62,74,83,82,99,71,93,74,46,88,69,74,73,85,86,84,82,71,66};
	bool matches = (test == expected1) || (test == expected2);
	REQUIRE(matches == true);
}
