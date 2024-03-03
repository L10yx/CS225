#include "Image.h"

namespace cs225{
        Image::Image():PNG() {}
        Image::Image(unsigned int width, unsigned int height):PNG(width, height) {}
        Image::Image(Image const & other):PNG(other) {}
        Image::~Image() {}
        Image const & Image::operator=(Image const & other) {
            if (this != &other) { this->PNG::operator= (other); }
            return *this;
        }

        void Image::lighten () {
            for (unsigned i = 0; i < width(); i++) {
                for (unsigned j = 0; j < height(); j++) {
                    HSLAPixel* pixel = getPixel(i, j);
                    if (pixel->l <= 0.9) pixel->l += 0.1;
                    else pixel->l = 1;
                }
            }
        } //Lighten an Image by increasing the luminance of every pixel by 0.1.

        void Image::lighten (double amount) {
            for (unsigned i = 0; i < width(); i++) {
                for (unsigned j = 0; j < height(); j++) {
                    HSLAPixel* pixel = getPixel(i, j);
                    if (pixel->l + amount < 1) pixel->l += amount;
                    else pixel->l = 1;
                }
            }
        } //Lighten an Image by increasing the luminance of every pixel by amount.
 
        void Image::darken () {
            for (unsigned i = 0; i < width(); i++) {
                for (unsigned j = 0; j < height(); j++) {
                    HSLAPixel* pixel = getPixel(i, j);
                    if (pixel->l > 0.1) pixel->l -= 0.1;
                    else pixel->l = 0;
                }
            }
        } //Darken an Image by decreasing the luminance of every pixel by 0.1.
 
        void Image::darken (double amount) {
            for (unsigned i = 0; i < width(); i++) {
                for (unsigned j = 0; j < height(); j++) {
                    HSLAPixel* pixel = getPixel(i, j);
                    if (pixel->l - amount > 0) pixel->l -= amount;
                    else pixel->l = 0;
                }
            }
        } //Darkens an Image by decreasing the luminance of every pixel by amount.
 
        void Image::saturate (){
            for (unsigned i = 0; i < width(); i++) {
                for (unsigned j = 0; j < height(); j++) {
                    HSLAPixel* pixel = getPixel(i, j);
                    if (pixel->s <= 0.9) pixel->s += 0.1;
                    else pixel->s = 1;
                }                
            }
        } //Saturates an Image by increasing the saturation of every pixel by 0.1.
 
        void Image::saturate (double amount){
            for (unsigned i = 0; i < width(); i++) {
                for (unsigned j = 0; j < height(); j++) {
                    HSLAPixel* pixel = getPixel(i, j);
                    if (pixel->s + amount < 1) pixel->s += amount;
                    else pixel->s = 1;
                }
            }
        } //Saturates an Image by increasing the saturation of every pixel by amount.
 
        void Image::desaturate () {
            for (unsigned i = 0; i < width(); i++) {
                for (unsigned j = 0; j < height(); j++) {
                    HSLAPixel* pixel = getPixel(i, j);
                    if (pixel->s > 0.1) pixel->s -= 0.1;
                    else pixel->s = 0;
                }
            }
        } //Desaturates an Image by decreasing the saturation of every pixel by 0.1.
 
        void Image::desaturate (double amount) {
            for (unsigned i = 0; i < width(); i++) {
                for (unsigned j = 0; j < height(); j++) {
                    HSLAPixel* pixel = getPixel(i, j);
                    if (pixel->s - amount > 0) pixel->s -= amount;
                    else pixel->s = 0;
                }
            }
        } //Desaturates an Image by decreasing the saturation of every pixel by amount.
 
        void Image::grayscale (){
            for (unsigned i = 0; i < width(); i++) {
                for (unsigned j = 0; j < height(); j++) {
                    HSLAPixel* pixel = getPixel(i, j);
                    pixel->s = 0;
                }
            }
        } //Turns the image grayscale.
 
        void Image::rotateColor (double degrees) {
            for (unsigned i = 0; i < width(); i++) {
                for (unsigned j = 0; j < height(); j++) {
                    HSLAPixel* pixel = getPixel(i, j);
                    unsigned k = 0;
                    if (degrees > 0){
                        while(pixel->h + degrees - 360*k > 360){ 
                            k++;
                        }
                        pixel->h = pixel->h + degrees - 360*k;
                    }
                    else{
                        while(pixel->h + degrees + 360*k < 0){ 
                            k++;
                        }
                        pixel->h = pixel->h + degrees + 360*k;
                    }
                }
            }
        } //Rotates the color wheel by degrees.
 
        void Image::illinify () {  
            for (unsigned i = 0; i < width(); i++) {
                for (unsigned j = 0; j < height(); j++) {
                    HSLAPixel *pixel = getPixel(i, j);
                    if(pixel->h<113.5 or pixel->h >293.5) pixel->h = 11; // orange=11, blue=216, turn color closer to orange to orange
                    else pixel->h = 216; // turn color closer to blue to blue
                }
            }
        } //Illinify the image.
 
        void Image::scale (double factor) {
            
            Image* copy = new Image(*this);
            resize(int(factor * width()), int(factor * height()));
            for (unsigned i = 0; i < width(); i++) {
                for (unsigned j = 0; j < height(); j++) {
                    *getPixel(i, j) = *(copy->getPixel(i/factor, j/factor));
                }
            }
            delete copy;
        }  //Scale the Image by a given factor.
 
        void Image::scale (unsigned w, unsigned h){
            double factor = w/width();
            scale(factor);
        } //Scales the image to fit within the size (w x h).
}