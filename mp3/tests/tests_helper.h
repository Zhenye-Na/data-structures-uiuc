#ifndef TESTS_HELPER_H
#define TESTS_HELPER_H

#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"
#include "../list.h"

using namespace cs225;

class BlockPNG : public PNG
{
  public:
    PNG genImg(vector<int> vect, int d) {
        // error checking: we need to evenly divide the image into d by d blocks
        if (width() % d != 0 || height() % d != 0) {
            cerr << "[BlockPNG]: " << d << " does not divide either width "
                 << width() << " or height " << height() << endl;
            return PNG();
        }

        // error checking: vector must be of the correct length
        if (static_cast<size_t>((width() / d) * (height() / d)) != vect.size())
            cerr << "[BlockPNG]: Vector not of correct length (" << vect.size()
                 << " vs expected " << (width() / d) * (height() / d) << ")"
                 << endl;

        PNG ret;
        ret.resize(width(), height());

        int numWidth = width() / d;

        for (unsigned int i = 0; i < vect.size(); i++) {
            int idx = vect[i] % ((width() / d) * (height() / d) + 1);
            if (idx <= 0)
                idx = 1;

            // if idx is different, we modified it above---alert user
            if (idx != vect[i])
                cerr << "[BlockPNG]: Block number " << vect[i] << " not valid, "
                     << "truncated to " << idx << endl;

            int x = ((idx - 1) % numWidth) * d;
            int oy = ((idx - 1) / numWidth) * d;

            int y = oy;

            int sy = y + d;

            int nx = (i % numWidth) * d;
            int ny = (i / numWidth) * d;

            for (int j = nx; j < nx + d; j++) {
                for (int k = ny; k < ny + d; k++) {
                    ret.getPixel(j, k) = getPixel(x, y); // *operator()(x, y);
                    y++;
                    if (y == sy) {
                        y = oy;
                        x++;
                    }
                }
            }
        }

        return ret;
    }
};

inline vector<int> buildVector(BlockPNG const& b, int d)
{
    vector<int> v;
    for (size_t i = 1; i <= (b.width() * b.height()) / (d * d); i++)
        v.push_back(i);

    return v;
}

inline BlockPNG listToImage(List<HSLAPixel> const& list, unsigned width, unsigned height) {
    BlockPNG ret;
    ret.resize(width, height);
    vector<HSLAPixel> v(list.begin(), list.end());
    unsigned x = 0, y = 0;
    for (unsigned i = 0; i < v.size(); i++) {
        ret.getPixel(x, y) = v[i];
        y++;
        if (y == height) {
            y = 0;
            x++;
        }
    }
    return ret;
}

inline List<HSLAPixel> imageToList(PNG const& img, bool reverse = false) {
    List<HSLAPixel> list;
    for (unsigned i = 0; i < img.width(); i++) {
        for (unsigned j = 0; j < img.height(); j++) {
            if (reverse)
                list.insertFront(img.getPixel(i, j));
            else
                list.insertBack(img.getPixel(i, j));
        }
    }
    return list;
}

#endif
