/**
 * @file logfile_parser.h
 * Definition of a LogfileParser class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#ifndef _LOGFILE_PARSE_H_
#define _LOGFILE_PARSE_H_

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>

#include "lphashtable.h"
#include "schashtable.h"

/**
 * LogfileParser class: Provides an interface for querying logfiles of a
 * particular format.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
class LogfileParser
{
  public:
    /**
     * Constructs a new LogfileParser from the name of a log file.
     *
     * @param fname The name of the log file to open.
     */
    LogfileParser(const std::string& fname);

    /**
     * Determines if a given customer has ever visited the given url.
     *
     * @param customer The customer name.
     * @param url The url.
     * @return A boolean value indicating whether the customer visited
     *  the url.
     */
    bool hasVisited(const std::string& customer, const std::string& url) const;

    /**
     * Determines *when* a customer last visited a given url. If the
     * customer has not visited the given url, the output of this
     * function should be the default time_t.
     *
     * @param customer The customer name.
     * @param url The url.
     * @return A time_t representing when the customer last visited the
     *  given url.
     */
    time_t dateVisited(const std::string& customer,
                       const std::string& url) const;

    /**
     * Gets all of the unique urls that have been visited.
     *
     * @return A vector of urls that were visited in the logfile. Note
     *  that **there should be no duplicates in this vector**.
     */
    std::vector<std::string> uniquePages() const;

  private:
    /**
     * LogLine structure: Represents the information contained in a
     * single line of the logfile.
     *
     * @author Chase Geigle
     * @date Spring 2011
     * @date Summer 2012
     */
    class LogLine
    {
      public:
        /**
         * Constructs a LogLine from a string (actual physical line
         * in the logfile).
         *
         * @param line The line in the file to extract info from.
         */
        LogLine(const std::string& line);

        std::string customer; /**< The customer for this line, */
        std::string url;      /**< The url for this line. */
        time_t date;          /**< The date for this line. */
    };

    /**
     * HashTable used to determine when a customer visited a given url.
     *
     * Hint: think about what your key should be for this. How could
     * you construct a unique, string key to find information for a
     * given customer and url?
     */
    LPHashTable<std::string, time_t> whenVisitedTable;

    /**
     * Vector containing the unique urls found in the logfile. You
     * should fill this in the constructor.
     *
     * @note This vector **should not contain duplicates!**
     */
    std::vector<std::string> uniqueURLs;
};
#endif
