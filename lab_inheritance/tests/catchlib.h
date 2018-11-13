// be bad like catch and be header-only

#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <sstream>

/**
 * Compares two PNGs, reporting the (x, y) of the first offending pixel
 */

void compare_and_report(const PNG & test, const PNG & sol)
{
    if(test.width() != sol.width() || test.height() != sol.height())
    {
        std::stringstream s;
        s << "Sizes differ! Sol: (" << sol.width() << ", " << sol.height() << ") != Actual: (" ;
        s <<  test.width() << ", " << test.height() << ")";
        FAIL(s.str());
    }

    for(size_t y = 0, n = test.height(); y < n; y++)
        for(size_t x = 0, m = test.width(); x < m; x++)
        {
            if(test.getPixel(x, y) != sol.getPixel(x, y))
            {
                std::stringstream s;
                s << "Pixels differ at (" << x << ", " << y << ")!" << std::endl;
                s << "Sol: " << sol.getPixel(x, y) << ";  actual: " << test.getPixel(x, y) << std::endl;

                FAIL(s.str());
            }
        }

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

