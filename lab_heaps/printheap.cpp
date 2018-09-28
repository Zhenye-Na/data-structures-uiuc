// printheap.cpp
// Declares how to display a heap (using the printtree library)

#include "printtree.h"

template <class T, class Compare>
class HeapNodeDescriptor
    : public GenericNodeDescriptor<HeapNodeDescriptor<T, Compare>>
{
  public:
    HeapNodeDescriptor(const heap<T, Compare>& theHeap_, size_t index_)
        : theHeap(theHeap_), index(index_)
    {
    }
    bool isNull() const
    {
        return index >= theHeap._elems.size();
    }
    std::string key() const
    {
        std::stringstream ss;
        ss << theHeap._elems[index];
        return ss.str();
    }
    HeapNodeDescriptor left() const
    {
        return HeapNodeDescriptor(theHeap, theHeap.leftChild(index));
    }
    HeapNodeDescriptor right() const
    {
        return HeapNodeDescriptor(theHeap, theHeap.rightChild(index));
    }

  private:
    const heap<T, Compare>& theHeap;
    const size_t index;
};

template <class T, class Compare>
std::ostream& operator<<(std::ostream& out, const heap<T, Compare>& theHeap)
{
    if (theHeap._elems.size() - theHeap.root() < 64)
        printTree(HeapNodeDescriptor<T, Compare>(theHeap, theHeap.root()), out);

    if (theHeap._elems.size() - theHeap.root() < 200) {
        out << std::endl << "[ ";
        for (size_t i = theHeap.root(); i < theHeap._elems.size(); i++)
            out << theHeap._elems[i] << ' ';
        out << ']' << std::endl << std::endl;
    } else
        out << "(Size " << theHeap._elems.size() - theHeap.root() << " heap)"
            << std::endl
            << std::endl;

    return out;
}
