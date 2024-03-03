#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() :
 traversal_(nullptr), start_(Point(-1,-1)), tolerance_(0) {}

ImageTraversal::Iterator::Iterator(ImageTraversal &traversal, const Point & start, double tolerance) :
 points(1,start),traversal_(&traversal), start_(start), tolerance_(tolerance) {}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if (traversal_ == nullptr) return *this;
  if (!traversal_->points_s.empty()) return DFSpp();
  if (!traversal_->points_q.empty()) return BFSpp();
  traversal_ = nullptr;
  return *this;
}

ImageTraversal::Iterator & ImageTraversal::Iterator::DFSpp() {  
  while (!traversal_->points_s.empty()) {
    Point curr = traversal_->peek();
    bool flag = false;
    vector<Point> neighbor = traversal_->getDFSNeighbors(curr);
    for (int i = 0; i < (int)neighbor.size(); i++) {
      if (calculateDelta(traversal_->getPixel(curr), traversal_->getPixel(neighbor[i])) <= tolerance_) {
        traversal_->add(neighbor[i]);
        points.push_back(neighbor[i]);
        flag = true;
        break;
      }
    }
    if (flag) {
      return *this;
    }  
    traversal_->pop(); 
  }
  traversal_ = nullptr;
  return *this;
}
ImageTraversal::Iterator & ImageTraversal::Iterator::BFSpp() {
  while (!traversal_->points_q.empty()) {
    Point curr = traversal_->peek();
    vector<Point> neighbor = traversal_->getBFSNeighbors(curr);
    for (int i = 0; i < (int)neighbor.size(); i++) {
      if (calculateDelta(traversal_->getPixel(curr), traversal_->getPixel(neighbor[i])) <= tolerance_) {
        traversal_->add(neighbor[i]);
        points.push_back(neighbor[i]);
      }
    }
    traversal_->pop(); 
    if(traversal_->points_q.empty()) traversal_ = nullptr;
    return *this;
  }
  traversal_ = nullptr;
  return *this;
}


/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  if (traversal_ != nullptr) return traversal_->peek();
  return *points.end();
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return traversal_ != other.traversal_ ;
}


ImageTraversal::ImageTraversal() : png_(), start_(), tolerance_(0) {}

ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance) :
  png_(png), start_(start), tolerance_(tolerance), 
  visit(png_.width(), vector<bool>(png_.height(), false)) {}

HSLAPixel ImageTraversal::getPixel(Point p) const {
  if (p.x < png_.width() && p.y < png_.height())
    return *(png_.getPixel(p.x, p.y));
  return *(png_.getPixel(-1, -1));
}

vector<Point> ImageTraversal::getDFSNeighbors(Point p) const {
  vector<Point> neighbors;  
  if (p.y + 1 < png_.height() && !visit[p.x][p.y + 1])
    neighbors.push_back(Point(p.x, p.y + 1));
  if (p.x + 1< png_.width() && !visit[p.x + 1][p.y])
    neighbors.push_back(Point(p.x + 1, p.y));
  if (p.y >= 1 && !visit[p.x][p.y - 1])
    neighbors.push_back(Point(p.x, p.y - 1));
  if (p.x >= 1 && !visit[p.x - 1][p.y])
    neighbors.push_back(Point(p.x - 1, p.y));

  return neighbors;
}

vector<Point> ImageTraversal::getBFSNeighbors(Point p) const {
  vector<Point> neighbors;  

  if (p.x + 1 < png_.width() && !visit[p.x + 1][p.y])
    neighbors.push_back(Point(p.x + 1, p.y));
  if (p.y + 1 < png_.height() && !visit[p.x][p.y + 1])
    neighbors.push_back(Point(p.x, p.y + 1));
  if (p.x >= 1 && !visit[p.x - 1][p.y])
    neighbors.push_back(Point(p.x - 1, p.y));
  if (p.y >= 1 && !visit[p.x][p.y - 1])
    neighbors.push_back(Point(p.x, p.y - 1));
  return neighbors;
}