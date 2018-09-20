/**
 * Created: FA17
 *      Lab_trees
 *
 * Modified:
 *      By:
 */
 #define CATCH_CONFIG_RUNNER
 #include "catch.hpp"
 #include "catchlib.h"

 #include <unistd.h>
 #include <iostream>
 #include <algorithm>
 #include <ctype.h>
 #include <vector>
 #include "../binarytree.h"


 using namespace std;
 using namespace util;



 void assertMirror(vector<int> a, vector<int> b)
 {
     REQUIRE(a.size() == b.size());

     for(size_t i = 0; i < a.size(); i++){
         REQUIRE(a[i] == b[b.size()-1-i]);
     }
 }

 void assert_path(vector<vector <int> > a, vector<vector<int> > b)
 {
     REQUIRE(a.size() == b.size());
     for(size_t i = 0; i < a.size(); i++){
     	 REQUIRE(a[i].size() == b[i].size());
         for(size_t j=0; j<a[i].size();j++){
         REQUIRE(a[i][j]==b[i][j]);
	       }
     }
 }


 ////////////////////////////////////////////////////////////////
 //////////////////////// Start of Tests ////////////////////////
 ////////////////////////////////////////////////////////////////

TEST_CASE("test_mirror", "[weight=10"){
  vector<int> nodes;
	nodes.push_back(58); //         58
	nodes.push_back(35); //
	nodes.push_back(72); //    35        72
	nodes.push_back(10); //
	nodes.push_back(40); //  10  40    61  80
	nodes.push_back(61); //
	nodes.push_back(80); // 0 19            93
	nodes.push_back(93); //
	nodes.push_back(0); //
	nodes.push_back(19); //

  BinaryTree<int> tree;
  for(size_t i = 0; i < nodes.size(); i++)
    tree.insert(nodes[i], true);

  vector<int> beforeMirror;
  vector<int> afterMirror;

  tree.inOrder(beforeMirror);

  tree.mirror();

  tree.inOrder(afterMirror);

  assertMirror(beforeMirror, afterMirror);
}

TEST_CASE("test_isOrderedRecursive", "[weight=10]"){
    vector<int> ordering;
   	ordering.resize(10);
   	for(size_t i = 0; i < ordering.size(); i++)
   		ordering[i] = i;
   	srand( 1234 );
   	random_shuffle(ordering.begin(), ordering.end());

   	BinaryTree<int> tree;
   	for (size_t i = 0; i < ordering.size(); i++)
   		tree.insert(ordering[i]);

   	REQUIRE(tree.isOrderedRecursive() == false);

	  ordering.resize(12);
  	for (size_t i = 0; i < ordering.size(); i++)
  		ordering[i] = i;
  	srand( 1234 );
  	random_shuffle(ordering.begin(), ordering.end());

  	BinaryTree<int> tree2;
  	for (size_t i = 0; i < ordering.size(); i++)
  		tree2.insert(ordering[i], true);

  	REQUIRE(tree2.isOrderedRecursive() == true);
 }

 TEST_CASE("test_isOrderedIterative", "[weight=10]"){
    vector<int> ordering;
   	ordering.resize(10);
   	for(size_t i = 0; i < ordering.size(); i++)
   		ordering[i] = i;
   	srand( 1234 );
   	random_shuffle(ordering.begin(), ordering.end());

   	BinaryTree<int> tree;
   	for (size_t i = 0; i < ordering.size(); i++)
   		tree.insert(ordering[i]);

   	REQUIRE(tree.isOrderedIterative() == false);

	  ordering.resize(12);
  	for (size_t i = 0; i < ordering.size(); i++)
  		ordering[i] = i;
  	srand( 1234 );
  	random_shuffle(ordering.begin(), ordering.end());

  	BinaryTree<int> tree2;
  	for (size_t i = 0; i < ordering.size(); i++)
  		tree2.insert(ordering[i], true);

  	REQUIRE(tree2.isOrderedIterative() == true);
 }

 TEST_CASE("test_InorderTraversal", "[weight=10]"){
    vector<int> nodes;
	nodes.push_back(52); //         52
	nodes.push_back(39); //
	nodes.push_back(71); //    39         71
	nodes.push_back(17); //
	nodes.push_back(47); //  17   47     69   80
	nodes.push_back(69); //
	nodes.push_back(80); // 0 24             90
	nodes.push_back(90); //
	nodes.push_back(0); //
	nodes.push_back(24); //

	BinaryTree<int> tree;
	for(size_t i = 0; i < nodes.size(); i++)
		tree.insert(nodes[i], true);

	InorderTraversal<int> t(tree.getRoot());
  	TreeTraversal<int>::Iterator it = t.begin();
	REQUIRE( (*it)->elem == 0  ); ++it;
	REQUIRE( (*it)->elem == 17 ); ++it;
	REQUIRE( (*it)->elem == 24 ); ++it;
	REQUIRE( (*it)->elem == 39 ); ++it;
	REQUIRE( (*it)->elem == 47 ); ++it;
	REQUIRE( (*it)->elem == 52 ); ++it;  
	REQUIRE( (*it)->elem == 69 ); ++it;
	REQUIRE( (*it)->elem == 71 ); ++it;
	REQUIRE( (*it)->elem == 80 ); ++it;  
	REQUIRE( (*it)->elem == 90 ); ++it;

 }


TEST_CASE("test_printPaths", "[weight=10"){
	vector<int> nodes;
	nodes.push_back(52); //         52
	nodes.push_back(39); //
	nodes.push_back(71); //    39         71
	nodes.push_back(17); //
	nodes.push_back(47); //  17   47     69   80
	nodes.push_back(69); //
	nodes.push_back(80); // 0 24             90
	nodes.push_back(90); //
	nodes.push_back(0); //
	nodes.push_back(24); //

	BinaryTree<int> tree;
	for(size_t i = 0; i < nodes.size(); i++)
		tree.insert(nodes[i], true);

  vector<vector<int> > treePaths;
	tree.printPaths(treePaths);

	int arr[5][4] = {{52,39,17,0},{52,39,17,24},{52,39,47,-1},{52,71,69,-1},{52,71,80,90}};

  vector<vector <int> > treePathSolution;
	for(int i=0;i<5;i++){
  	vector<int> temp;
    for(int j=0; j<4; j++){
      if(arr[i][j]!=-1)
       temp.push_back(arr[i][j]);
     }
  	treePathSolution.push_back(temp);
	}
	assert_path(treePathSolution, treePaths);
}



TEST_CASE("test_sumDistances", "[weight=10]"){
 vector<int> nodes;
 nodes.push_back(50); //         50
 nodes.push_back(32); //
 nodes.push_back(70); //    32        70
 nodes.push_back(10); //
 nodes.push_back(45); //  10  45    69  88
 nodes.push_back(69);
 nodes.push_back(88);

 BinaryTree<int> tree;
 for(size_t i = 0; i < nodes.size(); i++)
   tree.insert(nodes[i], true);
 REQUIRE(10 == tree.sumDistances());
}

 int main(int argc, char* argv[])
 {
        srand(time(NULL));

    // put our beloved quotes
    print_quote("tests/quotes.txt");

   //  print_valgrind();

    int result = Catch::Session().run(argc, argv);

    return (result < 0xFF ? result : 0xFF);
 }
