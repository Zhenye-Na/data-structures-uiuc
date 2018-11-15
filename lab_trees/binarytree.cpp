/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
#include <stack>
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
  // Call recursive helper function on root
  return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
  // Base case
  if (subRoot == NULL)
    return -1;

  // Recursive definition
  return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
  // Call recursive helper function on the root
  printLeftToRight(root);

  // Finish the line
  cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
  // Base case - null node
  if (subRoot == NULL)
    return;

  // Print left subtree
  printLeftToRight(subRoot->left);

  // Print this node
  cout << subRoot->elem << ' ';

  // Print right subtree
  printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
  return mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node *& subRoot)
{
  if (subRoot == NULL) {
    return;
  }
  mirror(subRoot->left);
  mirror(subRoot->right);

  // swap left node and right node
  Node* tmp = subRoot->left;
  subRoot->left = subRoot->right;
  subRoot->right = tmp;
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
  InorderTraversal<int> iot(root);
  TreeTraversal<int>::Iterator it = iot.begin();
  T val = (*it)->elem;

  // iteratively check whether is ordered
	for (++it; it != iot.end(); ++it) {
		if (val > (*it)->elem) {
      return false;
    }
	}

  // if reach here, then is ordered
  return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
  return isOrderedRecursiveHelper(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursiveHelper(const Node* subRoot) const
{
  // root is NULL or root has no children
  if (subRoot == NULL || (subRoot->left == NULL && subRoot->right == NULL)) {
    return true;
  }

  // decresing order: left->elem > root->elem
  if (subRoot->left != NULL && subRoot->left->elem > subRoot->elem) {
    return false;
  }

  // decresing order: root->elem > right->elem
  if (subRoot->right != NULL && subRoot->right->elem < subRoot->elem) {
    return false;
  }

  // return true if left/right subtree is in ordered
  return (isOrderedRecursiveHelper(subRoot->left) && isOrderedRecursiveHelper(subRoot->right));
}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T>> &paths) const
{
  // your code here
  stack<Node*> nodes;
  if (root != NULL) {
      getPath(root, nodes, paths);
  }
}

template <typename T>
void BinaryTree<T>::getPath(Node * node, stack<Node*> &nodes, vector<vector<T>> &paths) const {
  if (node->left == NULL && node->right == NULL) {
    nodes.push(node);
    pushStacktoVector(nodes, paths);
    nodes.pop();
  }
  if (node->left != NULL) {
    nodes.push(node);
    getPath(node->left, nodes, paths);
    nodes.pop();
  }
  if (node->right != NULL) {
    nodes.push(node);
    getPath(node->right, nodes, paths);
    nodes.pop();
  }
}

template <typename T>
void BinaryTree<T>::pushStacktoVector(stack<Node*> nodes, vector<vector<T>> &paths) const {
  stack<Node*> reverse;
  vector<T> path;
  while (!nodes.empty()) {
    reverse.push(nodes.top());
    nodes.pop();
  }
  if (!reverse.empty()) {
    while (!reverse.empty()) {
      if (reverse.top() == NULL) {
        break;
      }
      path.push_back(reverse.top()->elem);
      reverse.pop();
    }
    paths.push_back(path);
  }
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
  return sumDistances(root, 0);
}

template <typename T>
int BinaryTree<T>::sumDistances(Node * node, int depth) const
{
  return node == NULL ? 0 : depth + sumDistances(node->left, depth + 1) + sumDistances(node->right, depth + 1);
}
