#include "HSLAPixel.h"

namespace cs225{
    HSLAPixel::HSLAPixel(){
        HSLAPixel::l = 1;
        HSLAPixel::a = 1;
    }
    HSLAPixel::HSLAPixel(double hue,double saturation,double luminance){
        HSLAPixel::a = 1;
        HSLAPixel::h = hue;
        HSLAPixel::s = saturation;
        HSLAPixel::l = luminance;
    }
    HSLAPixel::HSLAPixel(double hue,double saturation,double luminance,double alpha){
        HSLAPixel::a = alpha;
        HSLAPixel::h = hue;
        HSLAPixel::s = saturation;
        HSLAPixel::l = luminance;
    }
}