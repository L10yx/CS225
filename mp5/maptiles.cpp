/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource, vector<TileImage>& theTiles)
{
    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> points;
    map<Point<3>, int> map;
    for (int i = 0; i < (int)theTiles.size(); i++) {
        HSLAPixel color = theTiles[i].getAverageColor();
        Point<3> point(color.h / 360, color.s, color.l); // turn color into Point<3>
        points.push_back(point); // add to vector
        map.insert(pair<Point<3>, int>(point, i)); // add to map
    }
    KDTree<3> tree(points); // build tree
    for (int row = 0; row < canvas->getRows(); row++) {
        for (int col = 0; col < canvas->getColumns(); col++) {
            canvas->setTile(row, col, get_match_at_idx(tree, map, theTiles, theSource, row, col)); // use helperfunction
        }
    }
    return canvas;
}

TileImage* get_match_at_idx(const KDTree<3>& tree, map<Point<3>, int> tile_avg_map, 
vector<TileImage>& theTiles, const SourceImage& theSource, int row, int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
