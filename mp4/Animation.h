/**
 * @file Animation.h
 *
 * Defintion for a class that encapsulates creating animated images from a
 * set of PNG object frames.
 *
 * @author Wade Fagen-Ulmschneider
 * @date Fall 2017
 * 
 * @author Jack Toole
 * @date Fall 2011
 */
#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;

/**
 * Animation class---used to create animated images from a sequence of PNG
 * objects as frames of the animation.
 *
 * @author Wade Fagen-Ulmschneider
 * @date Fall 2017
 *
 * @author Jack Toole
 * @date Fall 2011
 */
class Animation
{
  public:
    /**
     * Adds a frame to the animation.
     *
     * @param img The image to be added.
     */
    void addFrame(const PNG& img);

    /**
     * Writes the animation to the file name specified.
     *
     * @param filename The name of the file to be written to.
     */
    void write(const std::string& filename);

    /**
     * Returns a frame at a specific index.
     *
     * @param index The zero-based index frame to return
     */
    PNG getFrame(unsigned index);

    /**
     * Returns the number of frames currently in the animation.
     */
    unsigned frameCount();


  private:
    std::vector<PNG> frames;

    template <typename T>
    string to_string(const T& value);
    string getString(int i, int padToSameLengthAs);
    bool exists(const string& path);
};

#endif
