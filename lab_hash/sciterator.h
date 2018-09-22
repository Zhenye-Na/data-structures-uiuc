#ifndef _SCITERATOR_H_
#define _SCITERATOR_H_
/** @cond STAFF */

/**
 * @file sciterator.h
 * Definition of the LPHashTable iterator implementation.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

/**
 * SCIteratorImpl: polymorphic iterator implementation class for
 * SCHashTables.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */
template <class K, class V>
class SCHashTable<K, V>::SCIteratorImpl : public HashTable<K, V>::HTIteratorImpl
{
  public:
    /**
     * We friend the SCHashTable class so that it may construct
     * iterator implementations with our private constructor.
     */
    friend class SCHashTable<K, V>;

    // for simplicity
    typedef typename HashTable<K, V>::HTIteratorImpl HTIteratorImpl;

    // inherited functions
    virtual void operator++();
    virtual bool operator==(const HTIteratorImpl& other) const;
    virtual const std::pair<K, V>& operator*();
    virtual HTIteratorImpl* clone() const;

    /**
     * Equality operator that compares two SCIteratorImpl. Used by the
     * generic operator==() for HTIteratorImpl after a successful
     * dynamic_cast down to SCIteratorImpl.
     *
     * @param other The SCIteratorImpl to compare against.
     * @return Whether the two implementations are the same.
     */
    virtual bool operator==(const SCIteratorImpl& other) const;

  private:
    /**
     * Reference to the table we are iterating over.
     */
    const SCHashTable& table;

    /**
     * Current bucket we are visiting.
     */
    size_t bucket;

    /**
     * Iterator over the lists in a given bucket.
     */
    typename std::list<std::pair<K, V>>::iterator bucket_iterator;

    /**
     * Hacky way of keeping track that we are at the end of the table.
     */
    bool end;

    /**
     * Private constructor: takes a SCHashTable to iterate over, an
     * integer for the bucket to start at, and a boolean indicating
     * whether we are at the end of the SCHashTable or not.
     *
     * @param ht The SCHashTable this iterator is going to be for.
     * @param i The bucket to start at.
     * @param ed Whether we are at the end of the SCHashTabe or not.
     */
    SCIteratorImpl(const SCHashTable& ht, size_t i, bool ed);
};
/** @endcond */
#include "sciterator.cpp"
#endif
