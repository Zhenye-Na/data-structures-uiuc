/**
 * @file heap.h
 * Definitinon of a heap class.
 */

#ifndef _HEAP_H_
#define _HEAP_H_

#include <vector>

// forward declare descriptor (used for printing, ignore)
template <class Type, class Comp>
class HeapNodeDescriptor;

/**
 * heap: A priority queue implemented as a heap.
 *
 * @author Chase Geigle
 * @date Fall 2012
 */
template <class T, class Compare = std::less<T>>
class heap
{
  public:
    /**
     * Constructs an empty heap.
     */
    heap();

    /**
     * Constructs a heap from a vector of elements by copying the
     * elements into the heap's storage and then running the buildHeap
     * algorithm.
     *
     * @param elems The elements that should be placed in the heap.
     */
    heap(const std::vector<T>& elems);

    /**
     * Removes the element with highest priority according to the
     * higherPriority() functor.
     *
     * @return The element with highest priority in the heap.
     */
    T pop();

    /**
     * Returns, but does not remove, the element with highest priority.
     *
     * @return The highest priority element in the entire heap.
     */
    T peek() const;

    /**
     * Inserts the given element into the heap, restoring the heap
     * property after the insert as appropriate.
     *
     * @param elem The element to be inserted.
     */
    void push(const T& elem);

    /**
     * Determines if the given heap is empty.
     *
     * @return Whether or not there are elements in the heap.
     */
    bool empty() const;

    /*Gets the vector of elems*/
    void getElems(std::vector<T> & heaped) const;

    /**
     * Prints the heap to an std::ostream. Given for you. Uses the helper
     * functions below to do its work, so please implement them!
     *
     * @param out The stream to be written to.
     * @param toPrint The heap to be printed.
     */
    template <class Type, class Comp>
    friend std::ostream& operator<<(std::ostream& out,
                                    const heap<Type, Comp>& toPrint);

    // friend descriptor to allow it to access private members
    friend class HeapNodeDescriptor<T, Compare>;

  private:
    /**
     * The internal storage for this heap. **You may choose whether
     * your heap is 0-based or 1-based (i.e., you are free to store the
     * root at either index 0 or index 1).** You should **pick one**, and
     * write the helper functions according to that choice.
     */
    std::vector<T> _elems;

    /**
     * Comparison functor. This functor takes two parameters and returns true
     * if the first parameter has a higher priority than the second.
     *
     * Compare is a template parameter and defaults to std::less, which creates
     * a min-heap. So, if `T = int` and `a = 3` and `b = 5`,
     * `higherPriority(a, b) = true` (`a < b`, so `a` has higher priority) and
     * `higherPriority(b, a) = false` (`b > a`, so `b` has lower priority)
     */
    Compare higherPriority;

    /**
     * Helper function that returns the root index of this heap.
     * Required for grading purposes! (This function should be
     * ridiculously easy: either return 0 if you plan to store the root
     * at index 0, or 1 if you plan on storing it at index 1).
     *
     * @return The index of the root node of the heap.
     */
    size_t root() const;

    /**
     * Helper function that returns the index of the left child of a
     * node in the heap. Required for grading purposes! (And it should
     * be useful to you as well).
     *
     * @param currentIdx The index of the current node.
     * @return The index of the left child of the current node.
     */
    size_t leftChild(size_t currentIdx) const;

    /**
     * Helper function that returns the index of the right child of a
     * node in the heap. Required for grading purposes! (And it should
     * be useful to you as well).
     *
     * @param currentIdx The index of the current node.
     * @return The index of the right child of the current node.
     */
    size_t rightChild(size_t currentIdx) const;

    /**
     * Helper function that returns the index of the parent of a node
     * in the heap.
     *
     * @param currentIdx The index of the current node.
     * @return The index of the parent of the current node.
     */
    size_t parent(size_t currentIdx) const;

    /**
     * Helper function that determines whether a given node has a
     * child.
     *
     * @param currentIdx The index of the current node.
     * @return A boolean indicating whether the current node has a
     *  child or not.
     */
    bool hasAChild(size_t currentIdx) const;

    /**
     * Helper function that returns the index of the child with the
     * highest priority as defined by the higherPriority() functor.
     *
     * For example, if T == int and the left child of the current node
     * has data 5 and the right child of the current node has data 9,
     * this function should return the index of the left child (because
     * the default higherPriority() behaves like operator<).
     *
     * This function assumes that the current node has children.
     *
     * @param currentIdx The index of the current node.
     * @return The index of the highest priority child of this node.
     */
    size_t maxPriorityChild(size_t currentIdx) const;

    /**
     * Helper function that restores the heap property by sinking a
     * node down the tree as necessary.
     *
     * @param currentIdx The index of the current node that is being
     *  sunk down the tree.
     */
    void heapifyDown(size_t currentIdx);

    /**
     * Helper function that restores the heap property by bubbling a
     * node up the tree as necessary.
     *
     * @param currentIdx The index of the current node that is being
     *  bubbled up the tree.
     */
    void heapifyUp(size_t currentIdx);
};

#include "heap.cpp"
#include "printheap.cpp"

#endif
