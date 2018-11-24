/**
 * @file skipList.cpp
 * MP6, skip list implementation
 */

#include "skipList.h"


/**
 * Default constructs the SkipList.
 * Uses two sentinel nodes, each initially of height 1
 */
SkipList::SkipList() {
    SkipNode* head_ = new SkipNode();
    SkipNode* tail_ = new SkipNode();

    head_->nodePointers[0].next = tail_;
    tail_->nodePointers[0].prev = head_;

    head_->key = INT_MIN;
    head_->value = HSLAPixel();

    tail_->key = INT_MAX;
    tail_->value = HSLAPixel();

    int listHeight_ = 1;
    int length_ = 0;

    int probability_ = 50;
    int maxLevel_ = 14;  // log(128 * 128)
}

/**
 * The assignment= operator.
 * @param other The SkipList to copy into ourselves.
 * @return The current object
 * @see copy()
 */
const SkipList& SkipList::operator=(const SkipList & other) {
    if(this != &other) {
        clear();
        copy(other);
    }

    return *this;
}



/**
 * Inserts a new node into the sorted order in the list, initialized with the provided values.
 * Will replace the value at key if it already exists
 * @param key The key to associate with the new Node
 * @param value The value to associate with the new Node
 */
void SkipList::insert(int key, HSLAPixel value) {
    SkipNode *temp = this->find(key);

    // If the SkipNode exists, the key exists in our list and the value for that key must
    // be updated to the new value.
    if (temp) {
        temp->value = value;
    }

    length_++;

    int newNodeLevel = levelGenerator();
    SkipNode * traverse = head_;
    int level = head_->nodePointers.size() - 1;

    // Set up traverse to point to the node right before where we want to insert
    while (traverse->nodePointers[0].next != tail_ && (level >= 0)) {
        int nextKey = traverse->nodePointers[level].next->key;

        if (key < nextKey) {
            level--;
            if (level < 0 ) { break; }
        } else  {
            traverse = traverse->nodePointers[level].next;
            level = traverse->nodePointers.size() - 1;
        }
    }

    // expand head_ and tail_ to encompass the new height of the list, if needed
    for(int i = listHeight_; i < max(this->listHeight_, newNodeLevel); i++) {
        head_->nodePointers.push_back(SkipPointer());
        tail_->nodePointers.push_back(SkipPointer());
    }
     
    this->listHeight_ = max(this->listHeight_, newNodeLevel);

    SkipNode * prev = traverse;
    SkipNode * forward = traverse->nodePointers[0].next;
    SkipNode * newNode = new SkipNode(key, value, newNodeLevel);

    int forwardLevel = 0;
    int backwardLevel = 0;

    int maxLevel = min(newNodeLevel, this->listHeight_);

    while (forwardLevel < maxLevel) {
        if (forward == tail_) {
            forward->nodePointers[forwardLevel].prev = newNode;
            newNode->nodePointers[forwardLevel].next = forward;
            forwardLevel++;
        } if (forward->nodePointers.size() > (size_t)forwardLevel) {
            forward->nodePointers[forwardLevel].prev = newNode;
            newNode->nodePointers[forwardLevel].next = forward;
            forwardLevel++;
        } else {
            forward = forward->nodePointers[0].next;
        }
    }

    while (backwardLevel < maxLevel) {
        if(prev == head_) {
            prev->nodePointers[backwardLevel].next = newNode;
            newNode->nodePointers[backwardLevel].prev = prev;
            backwardLevel++;
        } if (prev->nodePointers.size() > (size_t)backwardLevel) {
            prev->nodePointers[backwardLevel].next = newNode;
            newNode->nodePointers[backwardLevel].prev = prev;
            backwardLevel++;
        } else {
            prev = prev->nodePointers[0].prev;
        }
    }
}

/**
 * A function that searches for the given key and returns the associated HSLAPixel
 * Returns (0, 0, 0, 0.5) if it's not found
 * @param key The key to search for
 * @return The pixel with the specified key, or (0, 0, 0, 0.5) if not found
 */
HSLAPixel SkipList::search(int key) {
    SkipNode * retval = find(key);

    if (retval == NULL) {
        return retval->value;
    }

    return HSLAPixel(0, 0, 0, 0.5);
}

/**
 * Finds the given key in the list if it exists, and returns a pointer to the node containing it.
 * Randomly calls findR or findI
 * @param key The key to search for in the list
 * @return A pointer to the node containing key, or NULL if not found in the list
 */
SkipNode * SkipList::find(int key) {
    SkipNode * retval;

    if ((rand() % 2) == 0) { retval = findR(key); }
    else                   { retval = findI(key); }

    return retval;
}


/**
 * Finds the given key in the list if it exists, and returns a pointer to the node containing it.
 * @param key The key to search for in the list
 * @return A pointer to the node containing key, or NULL if not found in the list
 */
SkipNode * SkipList::findR(int key) {
    return findRHelper(key, head_->nodePointers.size() - 1, head_);
}

/**
 * Helper function for findR.
 * @param key The key to search for
 * @param level The level we're searching through
 * @param curr The current node we're searching through
 * @return A pointer to the node with the given key, or NULL if it could not be found
 */
SkipNode * SkipList::findRHelper(int key, int level, SkipNode * curr) {
    if (curr == tail_ || level < 0) {
        return NULL;
    }

    int nextKey =  curr->nodePointers[level].next->key;
    SkipNode* ret;

    // Base Case:
    if (nextKey == key) {
        ret = curr->nodePointers[level].next;
    }

    // Recusive Case:
    if (nextKey > key) {
        ret = findRHelper(key, level, curr);
    } else {
        ret = findRHelper(key, level, curr->nodePointers[level].next);    
    }

    return NULL;
}

/**
 * An iterative find function
 * @param key The key to search for
 * @return A pointer to the node with the given key, or NULL if it could not be found
 */
SkipNode * SkipList::findI(int key) {
    SkipNode * traverse = head_;
    SkipNode * retNode = NULL;

    int level = head_->nodePointers.size()-1;

    while (traverse->nodePointers[0].next != tail_ && level >= 0) {
        int nextKey = traverse->nodePointers[level].next->key;

        if (nextKey == key) {
            retNode = traverse->nodePointers[level].next;
        } else if (key < nextKey) {
            level--;
        } else {
            traverse = traverse->nodePointers[level].next;
            //level=traverse->nodePointers.size()-1; // slightly slows down code in our sorted inserts
        }

    }
    return NULL;
}



/**
 * Removes the node with the given key from the list.
 * @param key The key to search for and remove from the list
 * @return A boolean indicating whether a node was successfully removed from the list
 */
bool SkipList::remove(int key) {
    // don't allow the removal of sentinel nodes
    if(key == INT_MAX || key == INT_MIN)
        return false;

    SkipNode * node = find(key);
    bool ret = true;

    // can't remove a node that doesn't exist
    if(node == NULL) {
        ret = false;
    }

    length_--;

    // pass through all the pointers on either side of us
    for(size_t i = 0; i < node->nodePointers.size(); i++) {
        SkipNode * next = node->nodePointers[i].next;
        SkipNode * prev = node->nodePointers[i].prev;

        prev->nodePointers[i].next = next;
        next->nodePointers[i].prev = prev;
    }

    delete node;
    return true;
}


/**
 * A function that returns the keys of the list in a vector, using only next pointers.
 * @return a vector containing the keys from head_ to tail_, including the sentinel values
 */
vector<int> SkipList::traverse() {
    vector<int> ret;
    SkipNode * listPrintingTraverser = head_;

    while (listPrintingTraverser != tail_) {
        ret.push_back(listPrintingTraverser->key);
        listPrintingTraverser = listPrintingTraverser->nodePointers[0].next;
    }

    return ret;
}

