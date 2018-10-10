/**
 * @file maptiles.h
 *
 * mapTiles() function.
 * Developed for CS225 PhotoMosaic MP
 *
 * @author Jack Toole
 * @date Fall 2011
 */

#ifndef MAPTILES_H
#define MAPTILES_H

#include <map>
#include <vector>
#include "cs225/PNG.h"
#include "kdtree.h"
#include "mosaiccanvas.h"
#include "sourceimage.h"
#include "tileimage.h"

using namespace std;
using namespace cs225;

/**
 * Map the image tiles into a mosaic canvas which closely
 * matches the input image.
 *
 * @todo This function is required for MP 5.2.
 * @param theSource The input image to construct a photomosaic of
 * @param theTiles The tiles image to use in the mosaic
 */
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> & theTiles);

/**
 * Find the closest TileImage for a particular row and column.
 * This involves creating a representative TileImage to search
 * for, and querying the KDTree for the nearest neighbor
 *
 * @param tree The KDTree to search in
 * @param tile_avg_map Maps points to indices in the TileImage vector
 * @param theTiles Tiles to be used in the Photomosaic
 * @param theSource The image to make a Photomosaic of
 * @param row The row of the source image
 * @param col The column of the source image
 *
 * @returns the "nearest neighbor" tile
 */
TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col);
#endif // MAPTILES_H
