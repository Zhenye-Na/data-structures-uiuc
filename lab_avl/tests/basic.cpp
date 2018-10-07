#include "../cs225/catch/catch.hpp"

#include "../avltree.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;


// compare the two streams for equality
bool tree_equals_output(stringstream & s, string filename)
{
    ifstream file(filename);
    string soln_s;
    string out_s;

    while(getline(file, soln_s))
    {
        if(!getline(s, out_s))
            return false;

        if(out_s.compare(soln_s) != 0)
            return false;
    }
    if(getline(s, soln_s))
        return false;

    return true;
}


TEST_CASE("test_find", "[weight=10][valgrind]") {
	AVLTree<string, string> tree;
    tree.insert("C", "C++");
    tree.insert("free", "delete");
    tree.insert("malloc", "new");
    tree.insert("bool", "void");
    tree.insert("Nico", "nii");
    REQUIRE(tree.find("C").compare("C++") == 0);
    REQUIRE(tree.find("free").compare("delete") == 0);
    REQUIRE(tree.find("malloc").compare("new") == 0);
    REQUIRE(tree.find("bool").compare("void") == 0);
    REQUIRE(tree.find("Nico").compare("nii") == 0);

}

TEST_CASE("test_insert_small", "[weight=5]") {
    AVLTree<int, int> tree;
    tree.insert(1,2);
    tree.insert(4,5);
    tree.insert(5,4);
    vector<string> solnFuncCalls;
    vector<int> solnTraversal;
    vector<string> funcCalls = tree.getFunctionOrder();
    vector<int> inorderTraversal = tree.getInorderTraversal();
    stringstream str;
    tree.print(str, false);


    solnTraversal.push_back(1);
    solnTraversal.push_back(4);
    solnTraversal.push_back(5);

    solnFuncCalls.push_back("rotateLeft");

    REQUIRE(solnFuncCalls == funcCalls);
    REQUIRE(solnTraversal == inorderTraversal);
    REQUIRE(tree_equals_output(str, "tests/soln_test_insert_small.out") == true);
}

TEST_CASE("test_insert_find", "[weight=10]") {
    AVLTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(1, 1);
    tree.insert(8, 8);
    tree.insert(0, 0);
    tree.insert(3, 3);
    tree.insert(2, 2);
    vector<string> solnFuncCalls;
    vector<int> solnTraversal;
    vector<string> funcCalls = tree.getFunctionOrder();
    vector<int> inorderTraversal = tree.getInorderTraversal();

    solnTraversal.push_back(0);
    solnTraversal.push_back(1);
    solnTraversal.push_back(2);
    solnTraversal.push_back(3);
    solnTraversal.push_back(5);
    solnTraversal.push_back(8);

    solnFuncCalls.push_back("rotateLeftRight");
    solnFuncCalls.push_back("rotateLeft");
    solnFuncCalls.push_back("rotateRight");

    REQUIRE(solnFuncCalls == funcCalls);
    REQUIRE(solnTraversal == inorderTraversal);
    for (int i = 0; i < (int)solnTraversal.size(); i++) {
        REQUIRE(inorderTraversal[i] == tree.find(inorderTraversal[i]));
    }
}

TEST_CASE("test_insert_big", "[weight=10][valgrind]") {
    AVLTree<int, string> tree;

    vector< pair<int, string> > elems = {
        { 55, "" }, { 45, "" }, { 12, "" }, { 34, "" },
        { 56, "" }, { 46, "" }, { 13, "" }, { 35, "" },
        { 57, "" }, { 47, "" }, { 14, "" }, { 36, "" },
        { 58, "" }, { 48, "" }, { 15, "" }, { 37, "" }
    };

    for (auto p : elems)
    {
        tree.insert(p.first, p.second);
    }

    vector<string> solnFuncCalls =
    {
        "rotateRight",
        "rotateRightLeft",
        "rotateRight",
        "rotateLeft",
        "rotateLeft",
        "rotateLeft",
        "rotateLeft",
        "rotateLeft",
    };
    vector<string> funcCalls = tree.getFunctionOrder();
    vector<int> inorderTraversal = tree.getInorderTraversal();
    stringstream str;
    tree.print(str, false);

    vector<int> solnTraversal = {12, 13, 14, 15, 34, 35, 36, 37, 45, 46, 47, 48, 55, 56, 57, 58};


    REQUIRE(solnFuncCalls == funcCalls);
    REQUIRE(solnTraversal == inorderTraversal);
    REQUIRE(tree_equals_output(str, "tests/soln_test_insert_big.out") == true);
}

TEST_CASE("test_remove_small", "[weight=5]") {
    AVLTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(1, 1);
    tree.insert(8, 8);
    tree.insert(0, 0);
    tree.insert(3, 3);
    tree.insert(2, 2);

    for (int i = 0; i < 4; i++) {
        tree.remove(i);
    }

    vector<string> solnFuncCalls;
    vector<int> solnTraversal;
    vector<string> funcCalls = tree.getFunctionOrder();
    stringstream str;
    tree.print(str, false);


    solnFuncCalls.push_back("rotateLeftRight");
    solnFuncCalls.push_back("rotateLeft");
    solnFuncCalls.push_back("rotateRight");
    solnFuncCalls.push_back("rotateLeft");


    REQUIRE(tree_equals_output(str, "tests/soln_test_remove_small.out"));
}

TEST_CASE("test_remove_big", "[weight=10][valgrind]") {
    AVLTree<int, string> tree;

    vector< pair<int, string> > elems = {
        {94, ""}, {87, ""}, {61, ""},
        {96, ""}, {76, ""}, {92, ""},
        {42, ""}, {78, ""}, {17, ""},
        {11, ""}, {41, ""}, {95, ""},
        {36, ""}, {26, ""}, {23, ""},
        {93, ""}, {31, ""}, {3, ""},
        {45, ""}, {18, ""}, {73, ""},
        {24, ""}, {74, ""}, {1, ""},
        {71, ""}, {82, ""}
    };

    for (auto p : elems)
    {
        tree.insert(p.first, p.second);
    }


    vector<string> solnFuncCalls =
    {
        "rotateRight",
        "rotateRight",
        "rotateRight",
        "rotateRight",
        "rotateRightLeft",
        "rotateRight",
        "rotateLeft",
        "rotateLeft",
        "rotateLeftRight",
        "rotateLeft",
        "rotateRight",
        "rotateRight",
        "rotateLeft",
    };

    for (int r : {95, 94, 61, 76, 73, 71})
    {
        tree.remove(r);
    }

    vector<int> solnTraversal =
    {
        1, 3, 11, 17, 18, 23, 24, 26, 31, 36, 41, 42, 45, 74, 78, 82, 87, 92, 93, 96
    };
    vector<string> funcCalls = tree.getFunctionOrder();
    vector<int> inorderTraversal = tree.getInorderTraversal();
    stringstream str;
    tree.print(str, false);


    REQUIRE(solnFuncCalls == funcCalls);

    REQUIRE(solnTraversal == inorderTraversal);

    REQUIRE(tree_equals_output(str, "tests/soln_test_remove_big.out"));
}
