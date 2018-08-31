/**
 * @file room.h
 */

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <iostream>

#include "letter.h"

using namespace std;

/**
 * Represents a testing room, which has a group of letters allocated to it
 * (where letters are first letters of last names).
 */
class Room
{
  public:
    /** The room name */
    string name;

    /** The capacity of the room */
    int capacity;

    /** The number of students currently allocated */
    int count;

    /** The maximum size of the letters array (26) */
    int max_letters;

    /** An array of Letters currently allocated */
    Letter* letters;

    /** The number of valid Letters in the Letters array */
    int letterCount;

    /**
     * Room Default Constructor.
     * Creates a blank (uninitialized) room
     */
    Room();

    /**
     * Room copy constructor.
     * @param other The Room to copy into this room.
     */
    Room(const Room& other);

    /**
     * Main Room constructor.
     * Creates an empty room with the given name and capacity
     * @param init_name The name to create this Room with
     * @param init_capacity The size of this Room
     */
    Room(const string& init_name, int init_capacity);

    /**
     * Room assignment operator.
     * @param other The Room to make a copy of
     * @return A reference to the copied Room
     */
    Room& operator=(const Room& other);

    /**
     * Room destructor.
     */
    ~Room();

    /**
     * Allocates a letter group to this room.
     * @param L The letter group to add
     */
    void addLetter(const Letter& L);

    /**
     * @return the number of empty seats remaining in the room after
     *  current allocations.
     */
    int spaceRemaining();

    /**
     * Outputs the room to cout.
     *
     * @param stream The stream to print to
     */
    void print(std::ostream& stream = std::cout);

  private:
    /**
     * Destructor/assignment operator clear helper function.
     */
    void clear();

    /**
     * Cctor/assignment operator copy helper function.
     */
    void copy(const Room& other);
};

#endif
