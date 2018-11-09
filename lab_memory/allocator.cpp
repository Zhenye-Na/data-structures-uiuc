/**
 * @file allocator.cpp
 * @author Jack Toole, updated by Sean Massung to add doxygen comments
 * @date Fall 2011
 */

#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "allocator.h"
#include "fileio.h"

using namespace std;

/* copy Constructor */
Allocator::Allocator(const Allocator &other) {
    clear();
	  copy(other);
}

/* assignment operator */
Allocator &Allocator::operator=(const Allocator &other) {
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}

/* deconstructor */
Allocator::~Allocator() {
	  clear();
}

void Allocator::clear() {
	if (alpha != NULL)
		delete [] alpha;
	if (rooms != NULL)
		delete [] rooms;
}

void Allocator::copy(const Allocator &other) {
	  roomCount     = other.roomCount;
	  studentCount  = other.studentCount;
	  totalCapacity = other.totalCapacity;

    rooms = new Room[roomCount];
    for(int i = 0; i < roomCount; i++) {
    	rooms[i] = other.rooms[i];
    }

    alpha = new Letter[26];
    for(int i = 0; i < 26; i++) {
    	alpha[i] = other.alpha[i];
    }
}

Allocator::Allocator(const string& studentFile, const string& roomFile)
{
    createLetterGroups();
    loadStudents(studentFile);
    loadRooms(roomFile);
}

void Allocator::createLetterGroups()
{
    // Make letters (A - Z lettergroups)
    alpha = new Letter[26];
    for (int i = 0; i < 26; i++)
        alpha[i].letter = 'A' + i;
}

void Allocator::loadStudents(const string& file)
{
    // Read in students
    fileio::loadStudents(file);
    studentCount = fileio::getNumStudents();

    for (int i = 0; i < studentCount; i++) {
        string name = fileio::nextStudent();
        char letter = name[0];
        int index = (int)letter - 'A';
        alpha[index].addStudent();
    }
}

void Allocator::loadRooms(const string& file)
{
    // initialization for rooms
    roomCount = fileio::getNumRooms();

    // Read in rooms
    fileio::loadRooms(file);
    rooms = new Room[roomCount];

    totalCapacity = 0;
    int i = 0;
    while (fileio::areMoreRooms()) {
        rooms[i] = fileio::nextRoom();
        totalCapacity += rooms[i].capacity;
        i++;
    }
}


void Allocator::printStudents(std::ostream & stream /* = std::cout */)
{
    // Output number of each last letter name
    stream << "Student counts (" << studentCount << " total)" << endl;
    for (int i = 0; i < 26; i++)
        stream << alpha[i].letter << ": " << alpha[i].count << endl;
}

void Allocator::allocate()
{
    // Perform the allocation
    int border = solve();

    // Check for an error
    if (border < 0) {
        cerr << endl << "Cannot allocate all students." << endl << endl;
        exit(-1);
    }
}

void Allocator::printRooms(std::ostream & stream /* = std::cout */)
{
    // Output the allocation
    stream << "Room Allocation (" << studentCount << "/" << totalCapacity << ")"
         << endl;
    for (int i = 0; i < roomCount; i++)
        rooms[i].print(stream);
}

int Allocator::solve()
{
    stable_sort(alpha, alpha + 26);

    for (int L = 0; L < 26; L++) {
        Room* r = largestOpening();
        r->addLetter(alpha[L]);
    }

    return minSpaceRemaining();
}

int Allocator::minSpaceRemaining()
{
    int border = 1000000;
    for (int i = 0; i < roomCount; i++)
        if (rooms[i].spaceRemaining() < border)
            border = rooms[i].spaceRemaining();
    return border;
}

Room* Allocator::largestOpening()
{
    int index = 0;
    int max_remaining = 0;
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].spaceRemaining() > max_remaining) {
            index = i;
            max_remaining = rooms[i].spaceRemaining();
        }
    }
    return &rooms[index];
}
