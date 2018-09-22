/**
 * @file htiterator.cpp
 * Implementation of an iterator class over HashTables.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */
using std::pair;

template <class K, class V>
HashTable<K, V>::iterator::iterator()
    : impl(NULL)
{
    /* nothing */
}

template <class K, class V>
HashTable<K, V>::iterator::iterator(HTIteratorImpl* nimpl)
    : impl(nimpl)
{
    /* nothing */
}

template <class K, class V>
HashTable<K, V>::iterator::iterator(const iterator& other)
{
    copy(other);
}

template <class K, class V>
const typename HashTable<K, V>::iterator& HashTable<K, V>::iterator::
operator=(const iterator& other)
{
    if (this != &other) {
        clear();
        if (other.impl == NULL)
            impl = NULL;
        else
            impl = other.impl->clone();
    }
    return *this;
}

template <class K, class V>
HashTable<K, V>::iterator::~iterator()
{
    clear();
}

template <class K, class V>
void HashTable<K, V>::iterator::copy(const iterator& other)
{
    if (other.impl == NULL)
        impl = NULL;
    else
        impl = other.impl->clone();
}

template <class K, class V>
void HashTable<K, V>::iterator::clear()
{
    delete impl;
    impl = NULL;
}

template <class K, class V>
typename HashTable<K, V>::iterator& HashTable<K, V>::iterator::operator++()
{
    ++(*impl);
    return *this;
}

template <class K, class V>
typename HashTable<K, V>::iterator HashTable<K, V>::iterator::operator++(int)
{
    iterator tmp(*this);
    ++(*impl);
    return tmp;
}

template <class K, class V>
bool HashTable<K, V>::iterator::operator==(const iterator& rhs) const
{
    if (impl == NULL)
        return rhs.impl == NULL;
    if (rhs.impl == NULL)
        return impl == NULL;
    return *impl == *(rhs.impl);
}

template <class K, class V>
bool HashTable<K, V>::iterator::operator!=(const iterator& rhs) const
{
    return !(*this == rhs);
}

template <class K, class V>
const pair<K, V>& HashTable<K, V>::iterator::operator*()
{
    return *(*impl);
}

template <class K, class V>
const pair<K, V>* HashTable<K, V>::iterator::operator->()
{
    return &(*(*impl));
}
