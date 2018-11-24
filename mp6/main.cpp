/**
 * @file main.cpp
 * MP6, main function
 *
 * @author
 *  Arman Tajback
 *  Jordi Paris Ferrer
 */

// Feel free to modify this file to test more aspects of your list

#include "skipList.h"
#include <iostream>
#include <string>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"

using namespace cs225;
using namespace std;


/** 
 * Sets the global variable maxLevel to log_2 of imgSize
 * @param imgSize A power of two which gives how large of an image this list represents
 */
int maxLevelLog(int imgSize)  {
    int counter = 0;
    while (imgSize != 1) {
        imgSize = imgSize >> 1;
        counter++;
    }
    return counter;
}


/* 
 * Returns whether the given value is a power of two, using the magic of bitshifting
 * @param val The value to check for power-of-two-ness
 * @return Whether val was a power of two
 */
bool powerOf2(int val)  {
    unsigned int bitmask = 1;
    int counter = 0;

    if (val<0) { return false; }
    if ((val&(val-1))!=0) { return false; }
    return true;
}


/**
 * Returns a color represented by the string s.
 * @param s The string to parse into a color
 * @param d The default color to use if parsing failed
 * @return The color being represented by the input string
 */
HSLAPixel colorPicker(string s, HSLAPixel d = HSLAPixel(0,0 ,0))
{
    HSLAPixel color;

    if      (s == "black")  { color = HSLAPixel(  0, 1.0, 0.0); }
    else if (s == "red"  )  { color = HSLAPixel(  0, 1.0, 0.5); }
    else if (s == "green")  { color = HSLAPixel(120, 1.0, 0.5); }
    else if (s == "blue" )  { color = HSLAPixel(240, 1.0, 0.5); }
    else if (s == "white")  { color = HSLAPixel(  0, 1.0, 1.0); }
    else {
        cout << "Invalid color. Please choose one of the following: 'black', 'red', 'blue', 'green', 'white'" << endl;
        cout << "Using default of '" << d << "'" << endl;

        return d;
    }

    return color;
}

int main(int argc, char *argv[]) 
{
    // Setting seed for random number generator use time(NULL) for more random behavior
    // Seed it for deterministic numbers, useful for debugging
    //srand(225);
    srand(time(NULL));

    if (argc < 3 || argc > 5) {
        cout << argv[0] << " <image_size> <probability> [foreground color] [background color]" << endl;
        cout << argv[0] << " 64 4 red black" << endl;
        return 0;
    }

    int img_size = stoi(argv[1]);		
    int probability = stoi(argv[2]);
    HSLAPixel fore = HSLAPixel(0, 0, 0);
    HSLAPixel back = HSLAPixel(0, 0, 1);

    if (argc >= 4) {
        string c(argv[3]);
        transform(c.begin(), c.end(), c.begin(), ::tolower);
        fore = colorPicker(c, HSLAPixel(0, 0 , 0));
    }
    if (argc >= 5) {
        string c(argv[4]);
        transform(c.begin(), c.end(), c.begin(), ::tolower);
        back = colorPicker(c, HSLAPixel(0, 0 , 1));
    }
         
            

    /* Feel free to change 256 to 512 if you want a bigger image.
     *  Just be aware it will be very slow (it might be too big and break)!
     */
    if (!powerOf2(img_size) || img_size < 4 || img_size > 256)  {
        cout << "Please enter your an image size greater than 2 and less than 512 "
            "and as a power of 2."
            << endl;
        return 0;
    }

    if (probability > 100 || probability < 1) {
        cout << "`probability` must be an integer between 1 and 100 (You used " << probability << ")." << endl;
        return 0;
    }

    if(img_size >= 256) {
        cout << "Using large image size! out-structure.png will be generated but not viewable in the default editor!"
            " Use something like chrome to view (google-chrome out-structure.png &)" << endl;
    }

    
    HSLAPixel temp(10,11,12);
    SkipList * test = new SkipList(probability, maxLevelLog(img_size*img_size));

    for(int i = 0; i < img_size*img_size; i++) {
        test->insert(i, temp);
    }

    // @TODO: add more test cases to test your skiplist here!

    cout << "Value of search(4) " << (test->search(4) == temp ? "matches" : "doesn't match") << "expected output" << endl;

    test->printKeys();
    test->remove(4);
    test->printKeys();

    test->makeImage(img_size, fore, back).writeToFile("out-degenerate.png");
    test->toPNG(100, fore, back).writeToFile("out-structure.png");

    delete test;
    return 0;
}
