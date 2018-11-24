/**
 * @file frequency.cpp
 * Implementation of the Frequency storage class.
 *
 * @author Chase Geigle - Created
 * @author Nathan Walters - Modified
 * @date Summer 2012
 * @date Fall 2017
 */

#include "frequency.h"

Frequency::Frequency(int freq) : character_('\0'), frequency_(freq)
{
    // nothing
}

Frequency::Frequency(char c, int freq) : character_(c), frequency_(freq)
{
    // nothing
}

char Frequency::getCharacter() const
{
    return character_;
}

int Frequency::getFrequency() const
{
    return frequency_;
}

bool Frequency::operator<(const Frequency& other) const
{
    return frequency_ < other.frequency_;
}
