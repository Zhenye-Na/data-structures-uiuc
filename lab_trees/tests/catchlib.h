// be bad like catch and be header-only

#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

/**
 * Prints a warning to run the test cases in valgrind
 */
void print_valgrind()
{
        std::cout << "===============================================================================" << std::endl;
        std::cout << "===============================================================================" << std::endl;
        std::cout << "You may want to run these test cases in valgrind!" << std::endl;
        std::cout << "valgrind --leak-check=full ./test" << std::endl;
        std::cout << "===============================================================================" << std::endl;
        std::cout << "===============================================================================" << std::endl;
        std::cout << std::endl;
}

/**
 * Print a random quote from the file filename.
 *
 * @param filename The path to the quotes file
 */
void print_quote(std::string filename)
{

    std::vector<std::string> quotes;
    std::ifstream quote_file(filename);
    std::string line;

    while (std::getline(quote_file, line))
    {
        quotes.push_back(line);
    }

    if (quotes.size() > 0)
    {

        size_t index = rand() % quotes.size();

        std::cout << std::endl << std::endl;
        std::cout << "===============================================================================" << std::endl;
        std::cout << "===============================================================================" << std::endl;
        std::cout << "===============================================================================" << std::endl;
        std::cout << quotes[index] << std::endl;
        std::cout << "===============================================================================" << std::endl;
        std::cout << "===============================================================================" << std::endl;
        std::cout << "===============================================================================" << std::endl;
        std::cout << std::endl << std::endl;
    }
}

