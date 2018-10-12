/**
 * @file btree_given.cpp
 * Given function implementations for BTree.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <algorithm>

using std::vector;

/**
 * Constructs a default, order 64 BTree.
 */
template <class K, class V>
BTree<K, V>::BTree()
{
    root = nullptr;
    order = 64;
}

/**
 * Constructs a BTree with the specified order. The minimum order allowed
 * is order 3.
 * @param order The order of the constructed BTree.
 */
template <class K, class V>
BTree<K, V>::BTree(unsigned int order)
{
    root = nullptr;
    this->order = order < 3 ? 3 : order;
}

/**
 * Constructs a BTree as a deep copy of another.
 * @param other The BTree to copy.
 */
template <class K, class V>
BTree<K, V>::BTree(const BTree& other)
{
    clear(root);
    root = copy(other.root);
}

/**
 * Private recursive version of the copy function.
 * @param subroot A pointer to the current node being copied.
 */
template <class K, class V>
typename BTree<K, V>::BTreeNode* BTree<K, V>::copy(const BTreeNode* subroot)
{
    if (subroot == nullptr) {
        return nullptr;
    }

    BTreeNode* new_node = new BTreeNode(subroot);
    for (auto& child : subroot->children) {
        new_node->children.push_back(copy(child));
    }
    return new_node;
}

/**
 * Performs checks to make sure the BTree is valid. Specifically
 * it will check to make sure that an in-order traversal of the tree
 * will result in a sorted sequence of keys. Also verifies that each
 * BTree node doesn't have more nodes than its order.
 * @return true if it satisfies the conditions, false otherwise.
 */
template <class K, class V>
bool BTree<K, V>::is_valid(unsigned int order /* = 64 */) const
{
    if (root == nullptr)
        return true;
    vector<DataPair> data;
    return is_valid(root, data, order)
           && std::is_sorted(data.begin(), data.end());
}

/**
 * Private recursive version of the is_valid function.
 * @param subroot A pointer to the current node being checked for
 * validity.
 * @return true if the node is a valid BTreeNode, false otherwise.
 */
template <class K, class V>
bool BTree<K, V>::is_valid(const BTreeNode* subroot, vector<DataPair>& data,
                           unsigned int order) const
{
    if (subroot->elements.size() >= order) {
        return false;
    }

    auto first = subroot->elements.begin();
    auto last = subroot->elements.end();
    bool ret = subroot->children.size() == subroot->elements.size() + 1;
    if (!subroot->is_leaf) {
        auto curr_child = subroot->children.begin();
        ret &= is_valid(*curr_child, data, order);
        curr_child++;
        for (auto elem = first; ret && elem != last; elem++) {
            data.push_back(*elem);
            ret &= is_valid(*curr_child, data, order);
            curr_child++;
        }
    } else {
        data.insert(data.end(), first, last);
        ret = true;
    }
    return ret;
}

/**
 * Private recursive version of the clear function.
 * @param subroot A pointer to the current node being cleared.
 */
template <class K, class V>
void BTree<K, V>::clear(BTreeNode* subroot)
{
    if (!subroot->is_leaf) {
        for (auto child : subroot->children) {
            clear(child);
        }
    }
    delete subroot;
}

/**
 * Destroys a BTree.
 */
template <class K, class V>
BTree<K, V>::~BTree()
{
    clear();
}

/**
 * Assignment operator for a BTree.
 * @param rhs The BTree to assign into this one.
 * @return The copied BTree.
 */
template <class K, class V>
const BTree<K, V>& BTree<K, V>::operator=(const BTree& rhs)
{
    if (this != &rhs) {
        clear(root);
        root = copy(rhs.root);
    }
    return *this;
}

/**
 * Clears the BTree of all data.
 */
template <class K, class V>
void BTree<K, V>::clear()
{
    if (root != nullptr) {
        clear(root);
        root = nullptr;
    }
}
