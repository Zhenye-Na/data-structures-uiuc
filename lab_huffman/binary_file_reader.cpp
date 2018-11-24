/**
 * @file binary_file_reader.cpp
 * Implementation of a binary file class for input operations.
 *
 * @author Chase Geigle - Created
 * @author Nathan Walters - Modified
 * @date (created) Summer 2012
 * @date (modified) Fall 2017
 */

#include <iostream>
#include "binary_file_reader.h"

using namespace std;

BinaryFileReader::BinaryFileReader(const string& fileName)
    : file_(fileName, ios::binary), currentByte_('\0'), currentBit_(-1), numRead_(0)
{
    file_.seekg(-1, ios::end);
    maxBytes_ = file_.tellg();
    paddingBits_ = static_cast<int>(file_.get());
    file_.seekg(0, ios::beg);
}

BinaryFileReader::~BinaryFileReader()
{
    close();
}

void BinaryFileReader::close()
{
    if (file_.is_open())
        file_.close();
}

bool BinaryFileReader::hasBits() const
{
    return (numRead_ != maxBytes_) || (currentBit_ >= paddingBits_);
}

bool BinaryFileReader::hasBytes() const
{
    return (numRead_ != maxBytes_) || currentBit_ == 7;
}

bool BinaryFileReader::getNextBit()
{
    if (needsNextByte())
        readNextByte();
    bool ret = ((currentByte_ >> currentBit_) & 1) == 1;
    --currentBit_;
    return ret;
}

char BinaryFileReader::getNextByte()
{
    char ret = 0;
    for (int currBit = 0; currBit < 8 && hasBits(); ++currBit)
        ret = ret | getNextBit() << (7 - currBit);
    return ret;
}

bool BinaryFileReader::needsNextByte() const
{
    return currentBit_ == -1;
}

void BinaryFileReader::readNextByte()
{
    // read a single byte
    file_.read(&currentByte_, 1);
    currentBit_ = 7;
    ++numRead_;
}

void BinaryFileReader::reset()
{
    file_.seekg(0, ios::beg);
    currentBit_ = -1;
    currentByte_ = '\0';
}
