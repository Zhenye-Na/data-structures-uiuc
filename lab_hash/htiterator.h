/**
 * @file htiterator.h
 * Definition for an iterator class for HashTables.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */
#ifndef _HASHTABLE_ITERATOR_H_
#define _HASHTABLE_ITERATOR_H_

/**
 * Iterator for iterating over a hashtable.
 *
 * This example will print out all of the key, value pairs in the
 * HashTable variable `ht`:
 *
 *     for( HashTable::iterator it = ht.begin(); it != ht.end(); ++it )
 *         cout << "key: " << it->first << " value: " << it->second << endl;
 *
 * @author Chase Geigle
 * @date Summer 2012
 */
template <class K, class V>
class HashTable<K, V>::iterator
    : public std::iterator<std::forward_iterator_tag, std::pair<K, V>>
{
  public:
    // hash table can build iterators with our private constructor
    friend class HashTable<K, V>;

    /**
     * Constructs a default iterator.
     */
    iterator();

    /**
     * Copy constructor for an iterator.
     * @param other The iterator to be copied.
     */
    iterator(const iterator& other);

    /**
     * iterator assignment operator.
     * @param rhs The iterator to assign into the current iterator.
     * @return A reference to the current iterator for chaining.
     */
    const iterator& operator=(const iterator& rhs);

    /**
     * Destructor. Required since we are implementing polymorphic
     * iterators and need to free our implementation class upon going
     * out of scope.
     */
    ~iterator();

    /**
     * Pre-increment operator.
     */
    iterator& operator++();

    /**
     * Post-increment operator.
     */
    iterator operator++(int);

    /**
     * Compares whether two iterators are equal.
     * @param rhs The iterator to compare with.
     * @return Whether the current iterator is equal to the rhs.
     */
    bool operator==(const iterator& rhs) const;

    /**
     * Compares whether two iterators are unequal.
     * @param rhs The iterator to compare with.
     * @return Whether the two iterators are unequal.
     */
    bool operator!=(const iterator& rhs) const;

    /**
     * Dereference operator.
     */
    const std::pair<K, V>& operator*();

    /**
     * Dereference-access operator.
     */
    const std::pair<K, V>* operator->();

  private:
    /** @cond STAFF */
    /**
     * Creates an iterator from an implementation pointer.
     * @param nimpl A pointer to a new implementation on the heap.
     */
    iterator(HTIteratorImpl* nimpl);

    HTIteratorImpl* impl; /**< implementation for the iterator */

    /**
     * Helper function to copy a parameter iterator.
     * @param other The iterator to be copied.
     */
    void copy(const iterator& other);

    /**
     * Helper function to free dynamic memory associated with the
     * iterator.
     */
    void clear();
    /** @endcond */
};

/** @cond STAFF */
/**
 * HTIteratorImpl: an abstract iterator implementation class. Used by the
 * HashTable iterator class in order to be polymorphic across hash table
 * implementations. Derived classes of HashTable should implement their own
 * HTIteratorImpl and use it to construct their begin() and end()
 * iterators.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */
template <class K, class V>
class HashTable<K, V>::HTIteratorImpl
{
  public:
    /**
     * Destructor, provided as virtual in case derived classes use
     * dynamic memory.
     */
    virtual ~HTIteratorImpl()
    { /* nothing */
    }

    /**
     * Clones a given HTIteratorImpl: used in order to ensure that copy
     * constructing HashTable iterators works correctly.
     *
     * @return A pointer to a new HTIteratorImpl in the heap (should be
     *  of the derived class type).
     */
    virtual HTIteratorImpl* clone() const = 0;

    /**
     * Moves the iterator forward.
     */
    virtual void operator++() = 0;

    /**
     * Checks if two implementations are the same. Used when comparing
     * iterator equality. This should be overridden to dynamic_cast a
     * base class HTIteratorImpl to a derived class iterator
     * implementation to correctly do comparisons.
     *
     * @param other The other iterator implementation to compare
     *  against.
     * @return Whether the two iterator implementations are the same.
     */
    virtual bool operator==(const HTIteratorImpl& other) const = 0;

    /**
     * Checks if two implementations are not the same. Can be
     * overridden if necessary, but the default implementation should
     * suffice in most cases as it simply negates operator==().
     *
     * @param other The other iterator implementation to compare
     *  against.
     * @return Whether the two iterator implementations are unequal.
     */
    virtual bool operator!=(const HTIteratorImpl& other) const
    {
        return !(operator==(other));
    }

    /**
     * Dereference operator. Used by the HashTable iterator for its own
     * dereference operations.
     *
     * @return A const reference to the current key, value pair the
     *  iterator implementation is at.
     */
    virtual const std::pair<K, V>& operator*() = 0;
};
/** @endcond */
#include "htiterator.cpp"
#endif
