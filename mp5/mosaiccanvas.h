/**
 * @file mosaiccanvas.h
 *
 * Implementation of the mosaic data structure.
 *
 * @author Jack Toole
 * @author Matt Sachtler
 * @author Scott Wegner
 * @date Fall 2008
 * Developed for CS225 PhotoMosaic MP
 */

#ifndef MOSAICCANVAS_H
#define MOSAICCANVAS_H

#include <vector>
#include "cs225/PNG.h"
#include "tileimage.h"

using namespace std;
using namespace cs225;

/**
 * This is the actual mosaic data-structure which will hold the matrix
 * of sub-images to be written.  This is effectively just a 2-D array
 * of TileImage objects which can be accessed via convenience methods.
 */
class MosaicCanvas
{
  public:
    static bool enableOutput;

    /**
     * Default constructor
     *
     * @param theRows Number of rows to divide the canvas into
     * @param theColumns Number of columns to divide the canvas into
     */
    MosaicCanvas(int theRows, int theColumns);

    /**
     * Copy constructor
     *
     * @param source The MosaicCanvas object to copy
     */
    MosaicCanvas(const MosaicCanvas& source);

    /**
     * Retrieve the number of rows of images
     *
     * @return The number of rows in the mosaic, or -1 on error
     */
    int getRows() const;

    /**
     * Retrieve the number of columns of images
     *
     * @return The number of columns in the mosaic, or -1 on error
     */
    int getColumns() const;

    /**
     * Set the TiledImage for a particular region.  Note
     * that row and tile indices should be zero-based.
     *
     * @param row The row
     * @param column The column
     * @param img The TileImage to set
     *
     * @return 0 on success, or non-zero otherwise
     */
    void setTile(int row, int column, TileImage* img);

    /**
     * Retrieve the current TileImage for a particular
     * row and column.  If the row or column is out of
     * bounds, the default TileImage is returned.  Note
     * that row and tile indices should be zero-based.
     *
     * @param row The row
     * @param column The column
     *
     * @return The current TileImage for a particular,
     * or the default TileImage if none is set.
     */
    const TileImage& getTile(int row, int column);

    /**
     * Save the current MosaicCanvas as a file with
     * the following pixels per tile.
     * @param pixelsPerTile pixels per Photomosaic tile
     * @return the Photomosaic as a PNG object
     */
    PNG drawMosaic(int pixelsPerTile) ;

  private:
    /**
     * Number of image rows in the Mosaic
     */
    int rows;

    /**
     * Number of image columns in the Mosaic
     */
    int columns;

    /**
     * The actual matrix of Image data
     */
    vector<TileImage*> myImages;

    TileImage& images(int x, int y);
    //const TileImage& images(int x, int y) const;

    static uint64_t divide(uint64_t a, uint64_t b);
};

inline TileImage& MosaicCanvas::images(int row, int col)
{
    return *myImages[row * columns + col];
}
/**
inline const TileImage& MosaicCanvas::images(int row, int col) const
{
    return myImages[row * columns + col];
}
*/
inline uint64_t MosaicCanvas::divide(uint64_t a, uint64_t b)
{
    return (a + b / 2) / b;
}

#endif // _MOSAICCANVAS_H
