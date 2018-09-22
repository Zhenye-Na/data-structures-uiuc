/**
 * @file textfile.h
 * Definition of a text file reading interface.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
#ifndef _TEXTFILE_H_
#define _TEXTFILE_H_

#include <fstream>
#include <string>

/**
 * TextFile class: defines an interface for reading in a text file.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
class TextFile
{
  public:
    /**
     * Constructs a new TextFile from the given filename.
     *
     * @param filename The name of the file to read.
     */
    TextFile(const std::string& filename);

    /**
     * Destructor. Ensures our file is propery closed.
     */
    ~TextFile();

    /**
     * Determines whether more data can be read from the TextFile.
     *
     * @return True if there is more data to be read, false otherwise.
     */
    bool good();

    /**
     * Gets the next word in the file.
     *
     * @return The next word in the file.
     */
    std::string getNextWord();

  private:
    std::ifstream infile; /**< std::ifstream used for reading the file */
};
#endif
