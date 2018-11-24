/**
 * @file decoder.h
 * Definitions for functions for the decoder program.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#ifndef _DECODER_H_
#define _DECODER_H_

#include <string>
#include <vector>

/**
 * decoder namespace: collection of functions used for running the decoder
 * program.
 */
namespace decoder
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
     * Decodes a file using the given HuffmanTree.
     *
     * @param inputName Name of the file to be decompressed.
     * @param treeName Name of the file from which to read the HuffmanTree.
     * @param outputName Name of the file to write decompressed output to.
     */
    void decodeFile(const std::string& inputName, const std::string& treeName,
                    const std::string& outputName);
}

#endif
