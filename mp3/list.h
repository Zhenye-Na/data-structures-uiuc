/**
 * @file list.h
 * Doubly Linked List (MP 3).
 */
#ifndef _LIST_H_
#define _LIST_H_

#include <iterator>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * List: This is a templated linked list class (meaning it contains data of
 * templated type T, which is a placeholder for a type).
 *
 * You should not remove anything from this class definition, but
 * you will find it helpful to add your own helper functions to this class,
 * and are encouraged to add to it.
 */
template <class T>
class List {
  private:
    /**
     * The ListNode class is private to the List class via the principle of
     * encapsulation---the end user does not need to know our node-based
     * implementation details.
     */
    class ListNode {
      public:
        /**
         * Default ListNode constructor.
         * Implemented for you.
         * @see list_given.cpp
         */
        ListNode();

        /**
         * Constructs a ListNode with the given data.
         * Implemented for you.
         * @see list_given.cpp
         */
        ListNode(const T& ndata);

        /**
         * A pointer to the next node in the list. May be NULL
         * if one does not exist.
         */
        ListNode* next;

        /**
         * A pointer to the previous node in the list. May be NULL if
         * one does not exist.
         */
        ListNode* prev;

        /**
         * The data contained in this node. We do not allow you to
         * modify node data, so it is const.
         */
        const T data;
    };

  public:
    /**
     * Default List constructor.
     * Creates an empty List. Implemented for you.
     * @see list_given.cpp
     */
    List();

    /**
     * Copy constructor for a List.
     * Since Lists allocate dynamic memory (i.e., they use "new", we
     * must define the Big Three).
     * @see list_given.cpp
     *
     * @param other The list we are copying.
     */
    List(const List<T>& other);

    /**
     * Overloaded assignment operator for Lists.
     * Part of the Big Three that we must define because the class
     * allocates dynamic memory.
     * @see list_given.cpp
     *
     * @param rhs The right hand side of the assignment statement.
     */
    List<T>& operator=(const List<T>& rhs);

    /**
     * Gets the size of the List.
     * Defined as a const function because it promises not to modify
     * the current List in any way.
     * @see list_given.cpp
     *
     * @return The size of the current List.
     */
    int size() const;

    /**
     * Used to print the list.
     * Const because it promises not to modify the current List.
     * @see list_given.cpp
     *
     * @param os Output stream to print the list to (e.g. cout)
     */
    void print(ostream& os) const;

    /**
     * Determines if the current List is empty.
     * Const because it promises not to modify the current List.
     * @see list_given.cpp
     *
     * @return Boolean value of whether the current List is empty.
     */
    bool empty() const;

    // mp3.1 functions

    /**
     * Destroys the current List. This function should ensure that
     * memory does not leak on destruction of a list.
     */
    ~List();

    /**
     * Inserts a new node at the front of the List.
     * This function **SHOULD** create a new ListNode.
     *
     * @param ndata The data to be inserted.
     */
    void insertFront(const T& ndata);

    /**
     * Inserts a new node at the back of the List.
     * This function **SHOULD** create a new ListNode.
     *
     * @param ndata The data to be inserted.
     */
    void insertBack(const T& ndata);

    /**
     * Reverses the current List.
     */
    void reverse();

    /**
     * Reverses blocks of size n in the current List. You should use
     * your reverse( ListNode * &, ListNode * & ) helper function in
     * this method!
     *
     * @param n The size of the blocks in the List to be reversed.
     */
    void reverseNth(int n);

    /**
     * Modifies the List using the waterfall algorithm.
     * Every other node (starting from the second one) is removed from
     * the List, but appended at the back, becoming the new tail. This
     * continues until the next thing to be removed is either the tail
     * (**not necessarily the original tail!**) or NULL.  You may
     * **NOT** allocate new ListNodes.  Note that since the tail should
     * be continuously updated, some nodes will be moved more than
     * once.
     */
    void waterfall();

    /**
     * Splits the given list into two parts by dividing it at the
     * splitPoint.
     *
     * @param splitPoint Point at which the list should be split into two.
     * @return The second list created from the split.
     */
    List<T> split(int splitPoint);

    /**
     * Merges the given sorted list into the current sorted list.
     *
     * @param otherList List to be merged into the current list.
     */
    void mergeWith(List<T>& otherList);

    /**
     * Sorts the current list by applying the Mergesort algorithm.
     */
    void sort();

    // Provided Iterator Functions, don't remove
    #include "list-iter.h"

  private:
    /*
     * Private member variables.
     *
     * You must use these as specified in the spec and may not rename them.
     * You may add more if you need them.
     */

    /**
     * The head of the List. May be NULL if the List is empty.
     */
    ListNode* head_;

    /**
     * The tail of the list. May be NULL if the List is empty.
     */
    ListNode* tail_;

    /**
     * The length of the current List. Do not forget to update it!
     */
    int length_;

    /*
     * Private helper functions.
     *
     * You must use these as specified in the spec and may not rename them.
     * You may place more here as you need them.
     */

    /**
     * Copies the given list into the current list.
     * @see list_given.cpp
     * @param other The List to be copied.
     */
    void copy(const List<T>& other); // implemented in list_given.cpp

    /**
     * Destroys all dynamically allocated memory associated with the
     * current List class.
     */
    void clear();

    /**
     * Helper function to reverse a sequence of linked memory inside a
     * List, starting at startPoint and ending at endPoint. You are
     * responsible for updating startPoint and endPoint to point to the
     * new starting and ending points of the rearranged sequence of
     * linked memory in question.
     *
     * @param startPoint A pointer reference to the first node in the
     *  sequence to be reversed.
     * @param endPoint A pointer reference to the last node in the
     *  sequence to be reversed.
     */
    void reverse(ListNode*& startPoint, ListNode*& endPoint);

    /**
     * Helper function to split a sequence of linked memory at the node
     * splitPoint steps **after** start. In other words, it should
     * disconnect the sequence of linked memory after the given number
     * of nodes, and return a pointer to the starting node of the new
     * sequence of linked memory.
     *
     * This function **SHOULD NOT** create **ANY** new List objects!
     *
     * @param start The node to start from.
     * @param splitPoint The number of steps to walk before splitting.
     * @return The starting node of the sequence that was split off.
     */
    ListNode* split(ListNode* start, int splitPoint);

    /**
     * Helper function to merge two **sorted** and **independent**
     * sequences of linked memory. The result should be a single
     * sequence that is itself sorted.
     *
     * This function **SHOULD NOT** create **ANY** new List objects.
     *
     * @param first The starting node of the first sequence.
     * @param second The starting node of the second sequence.
     * @return The starting node of the resulting, sorted sequence.
     */
    ListNode* merge(ListNode* first, ListNode* second);

    /**
     * Sorts a chain of linked memory given a start node and a size.
     * This is the recursive helper for the Mergesort algorithm
     * (i.e., this is the divide-and-conquer step).
     *
     * @param start Starting point of the chain.
     * @param chainLength Size of the chain to be sorted.
     * @return A pointer to the beginning of the now sorted chain.
     */
    ListNode* mergesort(ListNode* start, int chainLength);
};

// needed for template instantiation
#include "list-inl.h"

// this includes all of the functions that are given to you
// (i.e., the ones that you do not need to implement)
#include "list-given-inl.h"

#endif
