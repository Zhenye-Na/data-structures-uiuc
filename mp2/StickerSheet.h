/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */

 #include "Image.h"
 #include <iostream>

#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_

namespace cs225 {
  class StickerSheet: public Image {
  public:

    /**
      * Initializes this StickerSheet with a base picture and the ability to
      * hold a max number of stickers (Images) with indices 0 through max - 1.
      *
      * Parameters
      *   picture: The base picture to use in the StickerSheet
      *   max: The maximum number of stickers (Images) on this StickerSheet
      */
    StickerSheet(const Image & picture, unsigned max);

    /**
      * Frees all space that was dynamically allocated by this StickerSheet.
      */
    ~StickerSheet();

    /**
      * The copy constructor makes this StickerSheet an independent copy of the source.
      * Hint: Code is likely shared between all of the "Rule of Three" functions. Would a helper function (or two) make your life easier?
      *
      * Parameters
      *   other: The other StickerSheet object to copy data from
      */
    StickerSheet(const StickerSheet & other);


    /**
      * The assignment operator for the StickerSheet class.
      * Hint: Code is likely shared between all of the "Rule of Three" functions. Would a helper function (or two) make your life easier?
      *
      * Parameters
      *   other: The other Scene object to copy data from
      * Returns
      *   a constant Scene reference
      */
    const StickerSheet& StickerSheet::operator= (const StickerSheet & other);

    /**
      * Modifies the maximum number of stickers that can be stored on this
      * StickerSheet without changing existing stickers' indices.
      * If the new maximum number of stickers is smaller than the current number
      * number of stickers, the stickers with indices above max - 1 will be lost.
      *
      * Parameters
      *   max: The new value for the maximum number of Images in the StickerSheet.
      */
    void StickerSheet::changeMaxStickers(unsigned max);

    /**
      * Adds a sticker to the StickerSheet, so that the top-left of the
      * sticker's Image is at (x, y) on the StickerSheet.
      * The sticker must be added to the lowest possible layer available.
      *
      * Parameters
      *   sticker: The Image of the sticker.
      *   x: The x location of the sticker on the StickerSheet
      *   y: The y location of the sticker on the StickerSheet
      * Returns
      *   The zero-based layer index the sticker was added to, or -1 if the
      *   sticker cannot be added.
      */
    int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y);

    /**
      * Changes the x and y coordinates of the Image in the specified layer.
      *
      * If the layer is invalid or does not contain a sticker, this function
      * must return false. Otherwise, this function returns true.
      *
      * Parameters
      *   index: Zero-based layer index of the sticker.
      *   x: The new x location of the sticker on the StickerSheet
      *   y: The new y location of the sticker on the StickerSheet
      * Returns
      *   true: if the translate was successful; otherwise false.
      */
    bool StickerSheet::translate(unsigned index, unsigned x, unsigned y;

    /**
      * Removes the sticker at the given zero-based layer index.
      *
      * Parameters
      *   index The layer in which to delete the png
      */
    void StickerSheet::removeSticker(unsigned index);

    /**
      * Returns a pointer to the sticker at the specified index, not a copy of it.

      * That way, the user can modify the Image.
      * If the index is invalid, return NULL.
      *
      * Parameters
      *   index: The layer in which to get the sticker.
      * Returns
      *   A pointer to a specific Image in the StickerSheet.
      */
    Image* StickerSheet::getSticker(unsigned index) const;

    /**
      * Renders the whole StickerSheet on one Image and returns that Image.
      *
      * The base picture is drawn first and then each sticker is drawn in order
      * starting with layer zero (0), then layer one (1), and so on.
      *
      * If a pixel's alpha channel in a sticker is zero (0), no pixel is drawn
      * for that sticker at that pixel. If the alpha channel is non-zero,
      * a pixel is drawn. (Alpha blending is awesome, but not required.)
      *
      * The returned Image always includes the full contents of the picture and
      * all stickers. This means that the size of the result image may be larger
      * than the base picture if some stickers go beyond the edge of the picture.
      *
      * Returns
      *   an Image object representing the drawn scene
      */
    Image StickerSheet::render() const;

  }
};

#endif
