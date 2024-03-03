#include <string>
#include "cs225/PNG.h"

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
  PNG p1, p2;
    if(p1.readFromFile(inputFile)){
    p2 = PNG(p1);
      for (unsigned x = 0; x < p1.width(); x++) {
        for (unsigned y = 0; y < p1.height(); y++) {
        HSLAPixel *pixel = p2.getPixel(x, y);
        pixel->a = p1.getPixel(p1.width()-x-1,p1.height()-y-1)->a;
        pixel->h = p1.getPixel(p1.width()-x-1,p1.height()-y-1)->h;
        pixel->s = p1.getPixel(p1.width()-x-1,p1.height()-y-1)->s;
        pixel->l = p1.getPixel(p1.width()-x-1,p1.height()-y-1)->l;
        }
      }
    }
  p2.writeToFile(outputFile);
}