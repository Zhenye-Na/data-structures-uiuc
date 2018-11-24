/**
 * @file binary_file_writer.h
 * Definition of a binary file class for output operations.
 *
 * @author Chase Geigle - Created
 * @author Nathan Walters - Modified
 * @date (created) Summer 2012
 * @date (modified) Fall 2017
 */

#ifndef _BINARY_FILE_WRITER_H_
#define _BINARY_FILE_WRITER_H_

#include <fstream>
#include <string>

/**
 * BinaryFileWriter: interface for writing to binary files, bit by bit or
 * byte by byte. Wraps an ofstream in binary mode.
 */
class BinaryFileWriter
{
  public:
    /**
     * Constructs a new BinaryFileWriter by opening the given filename.
     *
     * @param fileName File to be opened.
     */
    BinaryFileWriter(const std::string& fileName);

    /**
     * Destroys an BinaryFileWriter: the destructor here ensures that
     * all remaining bits are written to the file before closing the
     * file. If the file was already closed, nothing is done.
     */
    ~BinaryFileWriter();

    /**
     * Writes the next bit of the file.
     *
     * @param bit The bit to be written.
     */
    void writeBit(bool bit);

    /**
     * Writes the next byte to the file.
     *
     * @param byte The byte to be written.
     */
    void writeByte(char byte);

    /**
     * Closes the given file.
     */
    void close();

  private:
    /**
     * std::ofstream used to write to the file.
     */
    std::ofstream file_; 

    /**
     * The current byte to write bits into.
     */
    char currentByte_;

    /**
     * The current bit within the currentByte that is being written.
     */
    int currentBit_;

    /**
     * Writes the current byte to the file.
     */
    void writeCurrentByte();
};
#endif
