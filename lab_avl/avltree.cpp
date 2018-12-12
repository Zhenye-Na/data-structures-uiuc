/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
  return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
  if (subtree == NULL)
    return V();
  else if (key == subtree->key)
    return subtree->value;
  else {
    if (key < subtree->key)
      return find(subtree->left, key);
    else
      return find(subtree->right, key);
  }
}

template <class K, class V>
void AVLTree<K, V>::calculateHeight(Node*& subtree) {
  if (subtree->left == NULL && subtree->right == NULL) {
    subtree->height = 0;
  } else if (subtree->left  == NULL) {
    subtree->height = subtree->right->height + 1;
  } else if (subtree->right == NULL) {
    subtree->height = subtree->left->height  + 1;
  } else {
    subtree->height = max(subtree->right->height, subtree->left->height) + 1;
  }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
  functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
  // your code here
  if (t == NULL || t->right == NULL) {
    return;
  }

  Node* oldRoot = t;
  Node* newRoot = t->right;
  Node* movingChild = t->right->left;

  t = newRoot;
  oldRoot->right = movingChild;
  newRoot->left = oldRoot;

  calculateHeight(oldRoot);
  calculateHeight(newRoot);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
  functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
  // Implemented for you:
  rotateLeft(t->left);
  rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
  functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
  // your code here
  if (t == NULL || t->left == NULL) {
    return;
  }

  Node* oldRoot = t;
  Node* newRoot = t->left;
  Node* movingChild = t->left->right;

  t = newRoot;
  oldRoot->left = movingChild;
  newRoot->right = oldRoot;

  calculateHeight(oldRoot);
  calculateHeight(newRoot);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
  functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
  // your code here
  rotateRight(t->right);
  rotateLeft(t);
}

template <class K, class V>
int AVLTree<K, V>::balance(Node*& subtree) {
  if (subtree == NULL)
    return 0;
  int leftHeight  = heightOrNeg1(subtree->left);
  int rightHeight = heightOrNeg1(subtree->right);
  return leftHeight - rightHeight;
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
  // your code here
  if (subtree == NULL) {
    return;
  }

  calculateHeight(subtree);

  int treeBalance = balance(subtree);
  if (abs(treeBalance) <= 1)
    return;

  if (treeBalance < 0) {                // tree is right heavy
    if (balance(subtree->right) > 0) {  // tree's right subtree is left heavy
      rotateRightLeft(subtree);
    } else {
      rotateLeft(subtree);
    }
  } else {                              // left heavy
    if (balance(subtree->left) < 0) {   // tree's left subtree is right heavy
      rotateLeftRight(subtree);
    } else {
      rotateRight(subtree);
    }
  }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
  insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
  // your code here
  if (subtree == NULL) {
    subtree = new Node(key, value);
  } else if (subtree->key == key) {
    subtree->value = value;
  } else if (key < subtree->key) {
    insert(subtree->left, key, value);
    rebalance(subtree);
  } else {
    insert(subtree->right, key, value);
    rebalance(subtree);
  }

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
  remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
  if (subtree == NULL)
    return;

  if (key < subtree->key) {
    remove(subtree->left, key);
    rebalance(subtree);
  } else if (key > subtree->key) {
    // your code here
    remove(subtree->right, key);
    rebalance(subtree);
  } else {
    if (subtree->left == NULL && subtree->right == NULL) {
      /* no-child remove */
      // your code here
      delete subtree;
      subtree = NULL;
    } else if (subtree->left != NULL && subtree->right != NULL) {
      /* two-child remove */
      // your code here
      Node*& IOP = rightMostNode(subtree->left);
      swap(IOP, subtree);
      delete IOP;
      IOP = NULL;
    } else {
      /* one-child remove */
      // your code here
      Node* subtreeNewChild = subtree->left != NULL ? subtree->left : subtree->right;
      delete subtree;
      subtree = subtreeNewChild;
    }
    // your code here
    rebalance(subtree);
  }
}

template <class K, class V>
typename AVLTree<K, V>::Node*& AVLTree<K, V>::rightMostNode(Node*& subtree) {
  return subtree->right == NULL ? subtree : rightMostNode(subtree->right);
}
