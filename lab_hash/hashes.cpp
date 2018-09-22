/**
 * @file hashes.cpp
 * Implementation of specialized hash functions for different key types.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#include "hashes.h"

namespace hashes
{
    /**
     * Specialized hash() function for character keys.
     */
    template <>
    unsigned int hash(const char& key, int size)
    {
        // simple hash, probably could be better
        return static_cast<unsigned char>(key) % size;
    }

    /**
     * Specialized hash() function for std::string keys.
     */
    template <>
    unsigned int hash(const std::string& key, int size)
    {
        // Bernstein Hash
        unsigned int h = 0;
        for (size_t i = 0; i < key.length(); ++i)
            h = 33 * h + key[i];
        return h % size;
    }
}
