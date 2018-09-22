#ifndef _LPITERATOR_H_
#define _LPITERATOR_H_
/** @cond STAFF */

/**
 * @file lpiterator.h
 * Definition of the LPHashTable iterator implementation.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

/**
 * LPIteratorImpl: polymorphic iterator implementation class for
 * LPHashTables.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */
template <class K, class V>
class LPHashTable<K, V>::LPIteratorImpl : public HashTable<K, V>::HTIteratorImpl
{
  public:
    /**
     * We friend the LPHashTable class so that it may construct
     * iterator implementations with our private constructor.
     */
    friend class LPHashTable<K, V>;

    // for simplicity
    typedef typename HashTable<K, V>::HTIteratorImpl HTIteratorImpl;

    // inherited functions
    virtual void operator++();
    virtual bool operator==(const HTIteratorImpl& other) const;
    virtual const std::pair<K, V>& operator*();
    virtual HTIteratorImpl* clone() const;

    /**
     * Equality operator that compares two LPIteratorImpl. Used by the
     * generic operator==() for HTIteratorImpl after a successful
     * dynamic_cast.
     *
     * @param other The LPIteratorImpl to compare against.
     * @return Whether the two implementations are the same.
     */
    virtual bool operator==(const LPIteratorImpl& other) const;

  private:
    /**
     * The current bucket we are at in the LPHashTable's internal
     * array.
     */
    size_t bucket;

    /**
     * Reference to the LPHashTable we are iterating over.
     */
    const LPHashTable<K, V>& table;

    /**
     * Private constructor: takes a LPHashTable to iterate over and a
     * bucket index to start at.
     *
     * @param ht The LPHashTable this iterator is going to be for.
     * @param i The bucket to start at.
     */
    LPIteratorImpl(const LPHashTable& ht, size_t i);
};
/** @endcond */
#include "lpiterator.cpp"
#endif
