#include "Image.h"
#include <iostream>

namespace cs225{
    class StickerSheet{
    public:

    StickerSheet ();

    StickerSheet (const Image &picture, unsigned max);
 	//Initializes this StickerSheet with a base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1. 
 
 	~StickerSheet ();
 	//Frees all space that was dynamically allocated by this StickerSheet. 
 
 	StickerSheet (const StickerSheet &other);
 	//The copy constructor makes this StickerSheet an independent copy of the source. 
 
    const StickerSheet & operator= (const StickerSheet &other);
 	//The assignment operator for the StickerSheet class. 
 
    void changeMaxStickers (unsigned max);
 	//Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices. 
 
    int addSticker (Image &sticker, unsigned x, unsigned y);
 	//Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet. 
 
    bool translate (unsigned index, unsigned x, unsigned y);
 	//Changes the x and y coordinates of the Image in the specified layer. 
 
    void removeSticker (unsigned index);
 	//Removes the sticker at the given zero-based layer index. 
 
    Image *getSticker (unsigned index) const;
 	//Returns a pointer to the sticker at the specified index, not a copy of it. 
 
    Image render () const;
 	//Renders the whole StickerSheet on one Image and returns that Image. 
    
    

    private:
    unsigned int width_;
    unsigned int height_;
    unsigned int layer_;
    unsigned int max_;
    unsigned int *x_;
    unsigned int *y_;

    Image *base_;
    Image **sheet_;
    Image *out_;

    //Copeies the contents of `other` to self
    void _copy(StickerSheet const & other);
    };
}