/**
 * @file skipList.h
 * MP6, skip list header file
 *
 * @author
 *  Arman Tajback
 *  Jordi Paris Ferrer
 *  Wade Fagen-Ulmschneider
 */

// You shouldn't have to modifty this file

#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <random>
#include <stdio.h>
#include <vector>
#include <cstdio>
#include <climits>
#include <algorithm>  
#include <string>
#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "skipNode.h"

using namespace cs225;

/**
 * A sorted Skip List class.
 */
class SkipList 
{
    public:

        /**
         * Default constructs the SkipList.
         * Uses two sentinel nodes, each initially of height 1
         */
        SkipList();

        /**
         * Constructs an empty list with the specified probability and maxlevel.
         * @param probability The probability of increasing the height of a node
         * @param maxlevel The maximum allowable height of the skiplist
         */
        SkipList(int probability, int maxlevel);

        /**
         * Constructs the SkipList with one initial node, which is constructed with the provided values.
         * 
         * @param key The key to associate with the initial node
         * @param value The pixel to associate with the initial node
         */
        SkipList(int key, HSLAPixel value);

        /**
         * Constructs the SkipList with one initial node, which is constructed with the provided values.
         * Also sets probability and maxlevel of the skiplist
         * 
         * @param key The key to associate with the initial node
         * @param value The pixel to associate with the initial node
         * @param probability The probability of increasing the height of a node
         * @param maxlevel The maximum allowable height of the skiplist

         */
        SkipList(int key, HSLAPixel value, int probability, int maxlevel);

        /**
         * Copy constructs the current SkipList.
         * @param other The SkipList to copy
         * @see copy()
         */
        SkipList(const SkipList &other);


        /**
         * The destructor for SkipList.
         * @see clear()
         */
        ~SkipList();

        /**
         * The assignment= operator.
         * @param other The SkipList to copy into ourselves.
         * @return The current object
         * @see copy()
         */
        const SkipList& operator=(const SkipList & other);

        /**
         * Inserts a new node into the sorted order in the list, initialized with the provided values.
         * @param key The key to associate with the new Node
         * @param value The value to associate with the new Node
         */
        void insert(int key, HSLAPixel value);

        /**
         * Removes the node with the given key from the list.
         * @param key The key to search for and remove from the list
         * @return A boolean indicating whether a node was successfully removed from the list
         */
        bool remove(int key);

        /**
         * Makes and returns an image showing how degenerate the list is.
         * The less degenerate the faster and more efficient the skip list will be.
         * More black pixels in the image == more degenerate
         * @param imgSize How large to make each side of the image
         * @param fg The color of the foreground, or degenerate pixels in this case
         * @param bg The color of the background, or normal pixels in this case
         * @return A pointer to a PNG representing how degenerate the list is
         */
        PNG makeImage(int imgSize, HSLAPixel fg, HSLAPixel bg);

        /**
         * Returns the height to use for the next node.
         * Is based on the probability and maxLevels global variables
         * @return The height to use for the next node
         */
        int levelGenerator();

        /**
         * A function that prints the keys of the list using only next pointers.
         */
        void printKeys();

        /**
         * A function that searches for the given key and returns the associated HSLAPixel
         * Returns (0, 0, 0, 50) if it's not found
         * @param key The key to search for
         * @return The pixel with the specified key, or (0, 0, 0, 50) if not found
         */
        HSLAPixel search(int key);

        /**
         * A function that prints the keys in the list using only prev pointers
         */
        void printKeysReverse();

        /**
         * A function that returns the keys of the list in a vector, using only next pointers.
         * @return a vector containing the keys from head to tail, including the sentinel values
         */
        vector<int> traverse();

        /**
         * A function that returns the keys of the list in a vector, using only prev pointers.
         * @return a vector containing the keys from head to tail, including the sentinel values
         */
        vector<int> traverseReverse();

        /**
         * A function that returns a PNG showing the structure of the current list
         * NOTE: This draws the sentinel nodes as well
         * @param maxHeight the height of the PNG; scales heights into the range [0, maxHeight)
         * @param fg The color to draw the nodes
         * @param bg The color of the background
         * @return a new PNG object representing the current list
         */
        PNG toPNG(int maxHeight = 100, HSLAPixel fg = HSLAPixel(0, 0, 0), HSLAPixel bg = HSLAPixel(0, 0, 1)) const;

    private:

        SkipNode *head_;
        SkipNode *tail_;

        int listHeight_ = 0;
        int length_ = 0;
        int probability_;
        int maxLevel_;


        /**
         * Finds the given key in the list if it exists, and returns a pointer to the node containing it.
         * @param key The key to search for in the list
         * @return A pointer to the node containing key, or NULL if not found in the list
         */
        SkipNode *findR(int key);

        /**
         * Helper function for findR.
         * @param key The key to search for
         * @param level The level we're searching through
         * @param curr The current node we're searching through
         * @return A pointer to the node with the given key, or NULL if it could not be found
         */
	    SkipNode *findRHelper(int key, int level, SkipNode * curr);
	
        /**
         * An iterative find function
         * @param key The key to search for
         * @return A pointer to the node with the given key, or NULL if it could not be found
         */
        SkipNode *findI(int key);

        /**
         * Finds the given key in the list if it exists, and returns a pointer to the node containing it.
         * Randomly calls findR or findI
         * @param key The key to search for in the list
         * @return A pointer to the node containing key, or NULL if not found in the list
         */
        SkipNode *find(int key);

        /**
         * A helper function for printKeysReverse().
         * @param curr The current node we are printing
         * @see printKeysReverse()
         */
        void printKeysReverse(SkipNode * curr);

        /**
         * A helper function for traverseReverse()
         * @param curr The current node
         * @param out The vector we are adding to
         */
        void traverseReverse(SkipNode * curr, vector<int> & out);

        /**
         * Clears up all memory associated with this SkipList
         */
        void clear();

        /**
         * The copy() helper method - used in the copy constructor and assignment= operator.
         * @param other The SkipList to copy into ourselves
         */
        void copy(const SkipList & other);

        /**
         * A function that will return the index-th SkipPointer from node.
         * Used because STL containers don't play well with gdb
         * @param node The node to consider
         * @param index The level of the node to get a SkipPointer for
         * @return A copy of the SkipPointer in node's index-th level
         */
        SkipPointer gdbGetPointer(SkipNode * node, size_t index) const;

        /**
         * A function that will get the current node's next and previous node's keys at each level
         * Used because STL containers don't play well with gdb.
         * @param node The node to get out
         * @return A string representing the node
         */
        string gdbGetNode(SkipNode * node) const;


        /**
         * A function that will print out the current node's next and previous node's keys at each level
         * Used because STL containers don't play well with gdb.
         * Note that this doesn't work well if you are using layour src
         * @param node The node to print out
         */
        void gdbPrintNode(SkipNode * node) const;
};


#endif

