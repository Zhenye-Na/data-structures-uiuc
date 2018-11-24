/**
 * @file encoder.h
 * Definitions for functions for the encoder program.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#ifndef _ENCODER_H_
#define _ENCODER_H_

#include <string>
#include <vector>

#include "frequency.h"

/**
 * encoder namespace: collection of functions used for running the encoder
 * program.
 */
namespace encoder
{
    /**
     * Main method of the program, should you choose to run it as a command
     * line version.
     *
     * @param args The command line arguments, with args[0] being the
     *	program name.
     */
    int main(const std::vector<std::string>& args);

    /**
     * Prints the usage of the command line version.
     *
     * @param programName The name of the program.
     */
    void printUsage(const std::string& programName);

    /**
     * Encodes a file using Huffman coding. Also creates the compressed
     * output of the HuffmanTree so it can be read in and used for
     * decompression.
     *
     * @param inputName Name of the file to be compressed.
     * @param outputName Name of the file to write compressed output.
     * @param treeName Name of the file to write the compressed
     *	HuffmanTree.
     */
    void encodeFile(const std::string& inputName, const std::string& outputName,
                    const std::string& treeName);

    /**
     * Determines the frequencies of characters in a string.
     *
     * @param str The string to be searched.
     * @return A vector of Frequency objects representing the frequency
     *	each character in the file has.
     */
    std::vector<Frequency> getFrequencies(const std::string& str);
}

#endif
