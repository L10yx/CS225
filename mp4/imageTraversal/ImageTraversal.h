#ifndef IMAGETRAVERSAL_H
#define IMAGETRAVERSAL_H

#include <stack>
#include <queue>
#include <iterator>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

using namespace cs225;

/**
 * A base class for traversal algorithms on images.
 * 
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  class Iterator : std::iterator<std::forward_iterator_tag, Point> {
  public:
    Iterator();
    Iterator(ImageTraversal &traversal, const Point & start, double tolerance);
    Iterator & operator++();

    Point operator*();
    bool operator!=(const Iterator &other);
    vector<Point> points;



  private:
    ImageTraversal *traversal_;
    Point start_;
    double tolerance_;
    Iterator & DFSpp();
    Iterator & BFSpp();
  };  

  ImageTraversal();
  ImageTraversal(const PNG & png, const Point & start, double tolerance);

  PNG png_;
  Point start_;
  double tolerance_;
  
  stack<Point> points_s;
  queue<Point> points_q;
  vector<vector<bool>> visit;
  virtual Iterator begin() = 0;
  virtual Iterator end() = 0;

  virtual void add(const Point & t) = 0;
  virtual Point pop() = 0;
  virtual Point peek() const = 0;
  virtual bool empty() const = 0;
  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);

  HSLAPixel getPixel(Point p) const;
  vector<Point> getDFSNeighbors(Point p) const;
  vector<Point> getBFSNeighbors(Point p) const;
  private:
    
};




#endif
