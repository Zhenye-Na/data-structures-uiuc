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
    StickerSheet(const Image & picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet & other);


    const StickerSheet& StickerSheet::operator=	(const StickerSheet & other);

    void StickerSheet::changeMaxStickers(unsigned max);

    int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y);

    bool StickerSheet::translate(unsigned index, unsigned x, unsigned y;

    void StickerSheet::removeSticker(unsigned index);

    Image* StickerSheet::getSticker(unsigned index) const;

    Image StickerSheet::render() const;

  }
};

#endif
