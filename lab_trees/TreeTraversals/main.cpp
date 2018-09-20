#include <algorithm>
#include <iostream>
#include "InorderTraversal.h"
#include "PreorderTraversal.h"

using namespace std;

int main() {
	BinaryTree<int> myTree;
	for (int i = 1; i <= 10; i++)
        myTree.insert(i);
	myTree.print();

	
	PreorderTraversal<int> pot(myTree.getRoot());
	cout<<"Preorder Traversal: ";
	for (TreeTraversal<int>::Iterator it = pot.begin(); it != pot.end(); ++it) {
		cout<<(*it)->elem<<" ";
	}
	cout<<endl;

	InorderTraversal<int> iot(myTree.getRoot());
	cout<<"Inorder Traversal:  ";
	for (TreeTraversal<int>::Iterator it = iot.begin(); it != iot.end(); ++it) {
		cout<<(*it)->elem<<" ";
	}
	cout<<endl;

}
