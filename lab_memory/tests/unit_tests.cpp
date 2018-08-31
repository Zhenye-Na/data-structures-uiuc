#include "catchlib.hpp"

#include <sstream>

#include "../allocator.h"
#include "../room.h"
#include "../letter.h"
#include "../fileio.h"

TEST_CASE("Test the constructor (valgrind)", "[weight=5][valgrind]")
{
	fileio::init();
	Allocator theAllocator("tests/students.txt", "tests/rooms.txt");
	fileio::halt();
}

TEST_CASE("Test allocate() (valgrind)", "[weight=5][valgrind]")
{
	fileio::init();
	Allocator theAllocator("tests/students.txt", "tests/rooms.txt");
    theAllocator.allocate();
	fileio::halt();
}

TEST_CASE("Test printRooms() (valgrind)", "[weight=20][valgrind]")
{
	fileio::init();
	Allocator theAllocator("tests/students.txt", "tests/rooms.txt");
    theAllocator.allocate();

    std::stringstream s;
    theAllocator.printRooms(s);

	fileio::halt();
}

TEST_CASE("Test printRooms() for overall output", "[weight=30]")
{
	fileio::init();
	Allocator theAllocator("tests/students.txt", "tests/rooms.txt");
    theAllocator.allocate();

    std::stringstream s;
    theAllocator.printRooms(s);
	fileio::halt();

    std::string str = s.str();
    bool contains = str.find("Room Allocation (237/248)") != std::string::npos;
    INFO((str + "\n\nMust contain: " + "Room Allocation (237/248)"));
    REQUIRE(contains);
}

TEST_CASE("Test printRooms() for individual output", "[weight=40]")
{
	fileio::init();
	Allocator theAllocator("tests/students.txt", "tests/rooms.txt");
    theAllocator.allocate();

    std::stringstream s;
    theAllocator.printRooms(s);
	fileio::halt();

    std::string str = s.str();
    std::vector<std::string> strings = 
    {
        "MEB 153 (31/32): W F",
        "MEB 218 (30/31): L H",
        "MEB 243 (29/30): S P Q",
        "MEB 335 (28/30): K R U V",
        "Siebel 1105 (24/24): G A X",
        "Siebel 1109 (23/24): M J I",
        "Siebel 1302 (20/21): Z N O",
        "Siebel 1304 (19/21): B D E",
        "BUR 140 (33/35): C Y T"
    };

    for (size_t i = 0; i < strings.size(); i++)
    {
        bool contains = str.find(strings[i]) != std::string::npos;

        INFO((str + "\n\nMust contain: " + strings[i]));

        REQUIRE(contains);
    }

}
