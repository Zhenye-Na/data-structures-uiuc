
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

using namespace std;

/**
 * Helper function that returns the root index of this heap.
 */
template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

/**
 * Helper function that returns the index of the left child of a node in the heap.
 *
 * @Parameters currentIdx The index of the current node.
 * @Returns The index of the left child of the current node.
 */
template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2 * currentIdx;
}

/**
 * Helper function that returns the index of the right child of a node in the heap.
 *
 * @Parameters currentIdx The index of the current node.
 * @Returns The index of the right child of the current node.
 */
template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2 * currentIdx + 1;
}

/**
 * Helper function that returns the index of the parent of a node in the heap.
 *
 * @Parameters currentIdx The index of the current node.
 * @Returns The index of the parent of the current node.
 */
template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx / 2;
}

/**
 * Helper function that determines whether a given node has a child.
 *
 * @Parameters currentIdx The index of the current node.
 * @Returns A boolean indicating whether the current node has a child or not.
 */
template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    return currentIdx * 2 < _elems.size();
}

/**
 * Helper function that returns the index of the child with the highest priority
 * as defined by the higherPriority() functor.
 *
 * For example, if T == int and the left child of the current node has data 5
 * and the right child of the current node has data 9, this function should
 * return the index of the left child (because the default higherPriority()
 * behaves like operator<).
 *
 * This function assumes that the current node has children.
 *
 * @Parameters currentIdx The index of the current node.
 * @Returns The index of the highest priority child of this node.
 */
template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if (rightChild(currentIdx) >= _elems.size())
        return leftChild(currentIdx);
    if (higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)]))
        return leftChild(currentIdx);
    else
        return rightChild(currentIdx);
}

/**
 * Helper function that restores the heap property by sinking a node down the
 * tree as necessary.
 *
 * Parameters currentIdx The index of the current node that is being sunk down the tree.
 */
template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if (!hasAChild(currentIdx))
        return;
    size_t minChild = maxPriorityChild(currentIdx);
    if (higherPriority(_elems[minChild], _elems[currentIdx])) {
        swap(_elems[minChild], _elems[currentIdx]);
        heapifyDown(minChild);
    }
}

/**
 * Helper function that restores the heap property
 * by bubbling a node up thetree as necessary.
 */
template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

/**
 * Constructs an empty heap.
 */
template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    T inf = numeric_limits<T>::min();
    _elems.push_back(inf);
}

/**
 * Constructs a heap from a vector of elements by copying the elements into the
 * heap's storage and then running the buildHeap algorithm.
 *
 * @Parameters elems The elements that should be placed in the heap.
 */
template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    T inf = numeric_limits<T>::min();
    _elems.push_back(inf);
    _elems.insert(_elems.end(), elems.begin(), elems.end());
    for (size_t i = parent(_elems.size()); i > 0; i--)
        heapifyDown(i);
}

/**
 * Removes the element with highest priority according to the higherPriority() functor.
 *
 * @Returns The element with highest priority in the heap.
 */
template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (empty())
        return T();
    T minValue = _elems[1];
    _elems[1] = _elems[_elems.size() - 1];
    _elems.pop_back();

    heapifyDown(1);
    return minValue;
}

/**
 * Returns, but does not remove, the element with highest priority.
 *
 * @Returns The highest priority element in the entire heap.
 */
template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[root()];
}

/**
 * Inserts the given element into the heap, restoring the heap property after
 * the insert as appropriate.
 *
 * @Parameters elem The element to be inserted.
 */
template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

/**
 * Determines if the given heap is empty.
 *
 * @Returns Whether or not there are elements in the heap.
 */
template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return (_elems.size() <= 1);
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
