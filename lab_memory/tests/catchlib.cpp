#include "catchlib.hpp"

namespace cs225
{

bool fileExists(std::string fileName) 
{
    std::ifstream f(fileName.c_str());
    bool exists = f.good();
    f.close();

    return exists;
}

void print_valgrind()
{
        std::cout << "===============================================================================" << std::endl;
        std::cout << "===============================================================================" << std::endl;
        std::cout << "You may want to run these test cases in valgrind!" << std::endl;
        std::cout << "valgrind --leak-check=full ./test" << std::endl;
        std::cout << "OR: " << std::endl;
        std::cout << "valgrind --leak-check=full ./test \"[valgrind]\"" << std::endl;
        std::cout << "===============================================================================" << std::endl;
        std::cout << "===============================================================================" << std::endl;
        std::cout << std::endl;
}


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

}
