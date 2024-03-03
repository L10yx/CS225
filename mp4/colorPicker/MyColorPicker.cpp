#include <cmath>

#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(HSLAPixel color, Point center, unsigned radius) : 
color(color), center(center), radius(radius) { }
/**
 * Picks the color for pixel (x, y).
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  double dy = y - center.y;
  double pct = dy / radius;

  if (pct >= 1) { return color; }

  double h = color.h; 
  double s = color.s * (1-pct);
  double l = color.l * (1-pct);
  double a = color.a * (1-pct);

  return HSLAPixel(h, s, l, a);
}
