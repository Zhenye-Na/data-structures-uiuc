/**
 * @file hashtable.h
 * Definition of an abstract HashTable interface.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <vector>
#include <cstddef>
#include <algorithm>

#include "hashes.h"

/**
 * HashTable: a templated class that implements the Dictionary ADT by using
 * a hash table.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
template <class K, class V>
class HashTable
{
  public:
    /**
     * Iterator for iterating over a hashtable.
     *
     * This example will print out all of the key, value pairs in the
     * HashTable variable `ht`:
     *
     *     for( HashTabe::iterator it = ht.begin(); it != ht.end(); ++it )
     *         cout << "key: " << it->first << " value: " << it->second << endl;
     */
    class iterator; // forward declare our iterator

    /**
     * Destructor for a HashTable: made virtual to allow overloading in
     * derived classes.
     */
    virtual ~HashTable()
    {
        /* nothing */
    };

    /**
     * Inserts the given key, value pair into the HashTable.
     *
     * @param key The key to be inserted.
     * @param value The value to be inserted.
     */
    virtual void insert(const K& key, const V& value) = 0;

    /**
     * Removes the given key (and its associated data) from the
     * HashTable.
     *
     * @param key The key to be removed.
     */
    virtual void remove(const K& key) = 0;

    /**
     * Finds the value associated with a given key.
     *
     * @param key The key whose data we want to find.
     * @return The value associated with this key, or the default value
     *    (V()) if it was not found.
     */
    virtual V find(const K& key) const = 0;

    /**
     * Determines if the given key exists in the HashTable.
     *
     * @param key The key we want to find.
     * @return A boolean value indicating whether the key was found in
     *    the HashTable.
     */
    virtual bool keyExists(const K& key) const = 0;

    /**
     * Empties the HashTable (that is, all keys and values are
     * removed).
     */
    virtual void clear() = 0;

    /**
     * Determines if the HashTable is empty. O(1).
     *
     * @note This depends on elems being set properly in derived
     *  classes.
     *
     * @return A boolean value indicating whether the HashTable is
     *  empty.
     */
    virtual bool isEmpty() const
    {
        return elems == 0;
    }

    /**
     * Used to determine the total size of the HashTable. Used for
     * grading purposes.
     *
     * @return The size of the HashTable (that is, the total number of
     *  available cells, not the number of elements the table
     *  contains).
     */
    virtual size_t tableSize() const
    {
        return size;
    }

    /**
     * Access operator: Returns a reference to a value in the
     * HashTable, so that it may be modified. If the key you are
     * searching for is not found in the table, this method inserts it
     * with the default value V() (which you then may modify).
     *
     * Examples:
     *
     *     hashtable["mykey"]; // returns the value for "mykey", or the
     *                         // default value if "mykey" is not in
     *                         // the table
     *
     *     hashtable["myOtherKey"] = "myNewValue";
     *
     * @param key The key to be found in the HashTable.
     * @return A reference to the value for this key contained in the
     *    table.
     */
    virtual V& operator[](const K& key) = 0;

    /**
     * Returns an iterator to the beginning of the HashTable.
     *
     * @return An iterator to the beginning of the HashTable.
     */
    virtual iterator begin() const = 0;

    /**
     * Returns an iterator to the end of the HashTable. Note that this
     * is essentially like returning an index to one past the final
     * element in an array (that is, end() itself gives an iterator to
     * one past the last thing in the HashTable).
     *
     * @return An iterator to the end of the HashTable.
     */
    virtual iterator end() const = 0;

  protected:
    size_t elems; /**< The current number of elements stored in the HashTable. */
    size_t size; /**< The current size of the HashTable (total cells). */

    class HTIteratorImpl; /**< Implementation for our iterator. You
                            don't have to worry about this. */

    /**
     * Helper function to create an iterator. You shouldn't have to
     * invoke this: instead, use the begin() and end() functions on
     * your particular HashTable implementation to get iterators to the
     * beginning and ending of the HashTable, respectively.
     *
     * @return An iterator for this HashTable.
     */
    iterator makeIterator(HTIteratorImpl* impl) const
    {
        return iterator(impl);
    }

    /**
     * Determines if the HashTable should resize.
     * @return Whether the HashTable should resize.
     */
    inline bool shouldResize() const
    {
        return static_cast<double>(elems) / size >= 0.7;
    }

    /**
     * List of primes for resizing.
     */
    static const size_t primes[];

    /**
     * Finds the closest prime in our list to the given number.
     *
     * @param num The number to find the closest prime to in our list.
     * @return The closest prime we have to num in our list of primes.
     */
    size_t findPrime(size_t num);

  private:
    /**
     * Private helper function to resize the HashTable. This should be
     * called when the load factor is >= 0.7 (this is somewhat
     * arbitrary, but used for grading).
     */
    virtual void resizeTable() = 0;
};

/**
 * List of primes for resizing. "borrowed" from boost::unordered.
 */
template <class K, class V>
const size_t HashTable<K, V>::primes[]
    = {17ul,         29ul,         37ul,        53ul,        67ul,
       79ul,         97ul,         131ul,       193ul,       257ul,
       389ul,        521ul,        769ul,       1031ul,      1543ul,
       2053ul,       3079ul,       6151ul,      12289ul,     24593ul,
       49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
       1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
       50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
       1610612741ul, 3221225473ul, 4294967291ul};

template <class K, class V>
size_t HashTable<K, V>::findPrime(size_t num)
{
    size_t len = sizeof(primes) / sizeof(size_t);
    const size_t* first = primes;
    const size_t* last = primes + len;
    const size_t* prime = std::upper_bound(first, last, num);
    if (prime == last)
        --prime;
    return *prime;
}

#include "htiterator.h"
#endif
