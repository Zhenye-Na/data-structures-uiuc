/** @cond STAFF */
/**
 * @file lpiterator.cpp
 * Implementation of the LPIteratorImpl implementation class.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */
/** @endcond */

using std::pair;

template <class K, class V>
LPHashTable<K, V>::LPIteratorImpl::LPIteratorImpl(const LPHashTable<K, V>& ht,
                                                  size_t j)
    : bucket(j), table(ht)
{
    if (bucket < table.size && table.table[bucket] == NULL)
        operator++();
}

template <class K, class V>
void LPHashTable<K, V>::LPIteratorImpl::operator++()
{
    while (++bucket < table.size && table.table[bucket] == NULL)
        ;
}

template <class K, class V>
bool LPHashTable<K, V>::LPIteratorImpl::
operator==(const HTIteratorImpl& rhs) const
{
    const HTIteratorImpl* tmp = &rhs;
    const LPIteratorImpl* other = dynamic_cast<const LPIteratorImpl*>(tmp);
    if (other == NULL)
        return false;
    else
        return *other == *this;
}

template <class K, class V>
bool LPHashTable<K, V>::LPIteratorImpl::
operator==(const LPIteratorImpl& rhs) const
{
    return &table == &rhs.table && bucket == rhs.bucket;
}

template <class K, class V>
pair<K, V> const& LPHashTable<K, V>::LPIteratorImpl::operator*()
{
    return *(table.table[bucket]);
}

template <class K, class V>
typename HashTable<K, V>::HTIteratorImpl*
LPHashTable<K, V>::LPIteratorImpl::clone() const
{
    return new LPIteratorImpl(table, bucket);
}
