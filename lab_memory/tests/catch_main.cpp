#define CATCH_CONFIG_RUNNER                     // we want our main

#include "catchlib.hpp"
#include "catch.hpp"

int main(int argc, char* argv[])
{
    // place us in the "tests" folder, where the tests and other files are
    //chdir("tests");

    // only print quotes if no arguments
    if(argc <= 1)
    {
        cs225::print_quote("quotes.txt");

        cs225::print_valgrind();
    }

    return Catch::Session().run(argc, argv);
}

