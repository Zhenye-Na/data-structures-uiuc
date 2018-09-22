/**
 * @file schashtable.h
 * Definition of the SCHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
#ifndef _SCHASHTABLE_H_
#define _SCHASHTABLE_H_

#include "hashtable.h"
#include <list>

/**
 * SCHashTable: A HashTable implementation that uses a separate chaining
 * collision resolution strategy.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
template <class K, class V>
class SCHashTable : public HashTable<K, V>
{
  private:
    // so we can refer to hash, elems, and size directly, and use the
    // makeIterator fuction without having to scope it.
    using HashTable<K, V>::elems;
    using HashTable<K, V>::size;
    using HashTable<K, V>::makeIterator;
    using HashTable<K, V>::findPrime;
    using HashTable<K, V>::shouldResize;

    // implementation for our iterator, you don't need to worry about
    // this
    class SCIteratorImpl;

  public:
    // we use HashTable's iterators here
    typedef typename HashTable<K, V>::iterator iterator;

    /**
     * Constructs a SCHashTable of the given size.
     *
     * @param tsize The desired number of starting cells in the
     *    SCHashTable.
     */
    SCHashTable(size_t tsize);

    /**
     * Destructor for the SCHashTable. We use dynamic memory, and thus
     * require the big three.
     */
    virtual ~SCHashTable();

    /**
     * Assignment operator.
     *
     * @param rhs The SCHashTable we want to assign into the current
     *    one.
     * @return A const reference to the current SCHashTable.
     */
    const SCHashTable<K, V>& operator=(const SCHashTable<K, V>& rhs);

    /**
     * Copy constructor.
     *
     * @param other The SCHashTable to be copied.
     */
    SCHashTable(const SCHashTable<K, V>& other);

    // functions inherited from HashTable
    virtual void insert(const K& key, const V& value);
    virtual void remove(const K& key);
    virtual V find(const K& key) const;
    virtual bool keyExists(const K& key) const;
    virtual void clear();
    virtual V& operator[](const K& key);

    iterator begin() const
    {
        return makeIterator(new SCIteratorImpl(*this, 0, false));
    }

    iterator end() const
    {
        return makeIterator(new SCIteratorImpl(*this, size, true));
    }

  private:
    /**
     * Storage for our SCHashTable.
     *
     * This is slightly ugly, but this is a dynamic array of standard
     * lists for the separate chaining strategy. The element inside
     * each list is a standard pair of K (key) and V (value).
     */
    std::list<std::pair<K, V>>* table;

    // inherited from HashTable
    virtual void resizeTable();
};
#include "sciterator.h"
#include "schashtable.cpp"
#endif
