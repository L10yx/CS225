#pragma once

#include "cs225/PNG.h"

namespace cs225{
    class Image:public PNG{
    public:
        Image();
        Image(unsigned int width, unsigned int height);
        Image(Image const & picture);
        ~Image();
        Image const & operator=(Image const & other);

        void	lighten (); //Lighten an Image by increasing the luminance of every pixel by 0.1.

        void	lighten (double amount); //Lighten an Image by increasing the luminance of every pixel by amount.
 
        void	darken (); //Darken an Image by decreasing the luminance of every pixel by 0.1.
 
        void	darken (double amount); //Darkens an Image by decreasing the luminance of every pixel by amount.
 
        void	saturate (); //Saturates an Image by increasing the saturation of every pixel by 0.1.
 
        void	saturate (double amount); //Saturates an Image by increasing the saturation of every pixel by amount.
 
        void	desaturate (); //Desaturates an Image by decreasing the saturation of every pixel by 0.1.
 
        void	desaturate (double amount); //Desaturates an Image by decreasing the saturation of every pixel by amount.
 
        void	grayscale (); //Turns the image grayscale.
 
        void	rotateColor (double degrees); //Rotates the color wheel by degrees.
 
        void	illinify (); //Illinify the image.
 
        void	scale (double factor); //Scale the Image by a given factor.
 
        void	scale (unsigned w, unsigned h); //Scales the image to fit within the size (w x h).
        
        void    rotate (int degree);
    };
}