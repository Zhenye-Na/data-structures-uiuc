/**
 * @file allocator.h
 * @author Jack Toole, updated by Sean Massung to add doxygen comments
 * @date Fall 2011
 */

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <iostream>

#include "letter.h"
#include "room.h"

/**
 * An allocator object to wrap the allocation of last-name letter groups
 * to rooms.
 */
class Allocator
{
  public:
    /**
     * Creates an Allocator object based on a list of students and a
     *  list of rooms.
     * @param studentFile Path to roster file
     * @param roomFile Path to room list file
     */
    Allocator(const string& studentFile, const string& roomFile);


    /**
     * Calls the solving routine to allocate student letter
     *  groups to rooms.
     */
    void allocate();

    /**
     * Prints each letter and how many students there are for each one.
     *
     * @param stream Where to print the results to
     */
    void printStudents(std::ostream & stream = std::cout);

    /**
     * Prints the room allocation determined by this Allocator.
     *
     * @param stream Where to print the results to
     */
    void printRooms(std::ostream & stream = std::cout);

  private:
    /**
     * Creates the array of letters.
     */
    void createLetterGroups();

    /**
     * Reads the students from the students file and places them in
     *  their letter groups.
     * @param file The file to read the student list from
     */
    void loadStudents(const string& file);

    /**
     * Reads rooms from the rooms file and sets their capacities.
     * @param file The file to read the room list from
     */
    void loadRooms(const string& file);


    /**
     * Runs the algorithm on the set of rooms and students.
     */
    int solve();

    /**
     * Return the room with the largest number of open seasts
     */
    Room* largestOpening();

    /**
     * Returns the amount of seats remaining in the room with the
     *  fewest spare seats.
     */
    int minSpaceRemaining();

    /** Array of all letters (size 26) */
    Letter* alpha;

    /** Array of all rooms */
    Room* rooms;

    /** Size of the rooms array */
    int roomCount;

    /** Total number of students */
    int studentCount;

    /** Total number of available seats across all rooms */
    int totalCapacity;
};

#endif
