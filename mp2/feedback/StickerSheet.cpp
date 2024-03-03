#include "StickerSheet.h"


namespace cs225{
    void StickerSheet::_copy(StickerSheet const & other){
        delete base_;
        delete out_;
        delete[] sheet_;
        delete[] x_;
        delete[] y_;
        // Clear self
        // Copy `other` to self

        width_ = other.width_;
        height_ = other.height_;
        max_ = other.max_;
        base_ = new Image(*(other.base_));
        out_ = new Image(*(other.base_));
        sheet_ = new Image*[max_];
        x_ = new unsigned int[max_];
        y_ = new unsigned int[max_];

        for (unsigned int i = 0; i < max_; i++) {
            sheet_[i] = other.sheet_[i];
            x_[i] = other.x_[i];
            y_[i] = other.y_[i];
        }
    }
    //Copeies the contents of `other` to self

    StickerSheet::StickerSheet () {
        
    }

    StickerSheet::StickerSheet (const Image &picture, unsigned int max){
        width_ = picture.width();
        height_ = picture.height();
        max_ = max;
        layer_ = 0;
        base_ = new Image(picture);
        out_ = new Image(picture);
        sheet_ = new Image*[max_];
        x_ = new unsigned int[max_];
        y_ = new unsigned int[max_];
        for (unsigned int i = 0; i < max_; i++) {
            sheet_[i] = NULL;
        }        
    }
 	//Initializes this StickerSheet with a base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1. 
 
 	StickerSheet::~StickerSheet (){
        delete base_;
        delete out_;
        delete[] sheet_;
        delete[] x_;
        delete[] y_;
    }
 	//Frees all space that was dynamically allocated by this StickerSheet. 
 
 	StickerSheet::StickerSheet (const StickerSheet &other){
        base_ = NULL;
        out_ = NULL;
        sheet_ = NULL;
        _copy(other);
    }
 	//The copy constructor makes this StickerSheet an independent copy of the source. 
 
    const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
        if (this != &other) { _copy(other); }
        return *this;
    }
 	//The assignment operator for the StickerSheet class. 
 
    void StickerSheet::changeMaxStickers (unsigned int max){
        if (max < max_) {
            while (max_ > max) {
                delete sheet_[max_-1];
                delete (sheet_ + max -1);
                delete (x_ + max_ - 1);
                delete (y_ + max_ - 1);
                max_ -= 1;
            }
            if (layer_ >= max) layer_ = max-1;
        }
        else {
            max_ = max;
        }
    }
 	//Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices. 
 
    int StickerSheet::addSticker (Image &sticker, unsigned int x, unsigned int y){
        for(unsigned int i = 0; i <= layer_; i++){
            if (sheet_[i] == NULL) {
                sheet_[i] = &sticker;
                x_[i] = x;
                y_[i] = y;
                return i;
            }
        }
        if ( layer_ < max_-1)  {
            layer_++;
            sheet_ [layer_] = &sticker;
            x_[layer_] = x;
            y_[layer_] = y;
            return layer_ ;
        }
        return -1;
    }
 	//Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet. 
 
    bool StickerSheet::translate (unsigned int index, unsigned int x, unsigned int y){
        if (sheet_[index] != NULL){
            x_ [index] = x;
            y_ [index] = y;
            return true;
        }
        return false;
    }
 	//Changes the x and y coordinates of the Image in the specified layer. 
 
    void StickerSheet::removeSticker (unsigned int index){
        delete sheet_[index];
        delete (sheet_ + index);
        delete (x_ + index);
        delete (y_ + index);
    }
 	//Removes the sticker at the given zero-based layer index. 
 
    Image *StickerSheet::getSticker (unsigned int index) const{
        if (index < max_) return sheet_[index];
        return NULL;
    }
 	//Returns a pointer to the sticker at the specified index, not a copy of it. 
 
    Image StickerSheet::render () const{
        *out_ = *base_;
        unsigned int i = 0;
        while( i < max_ ) {
            if(sheet_[i] != NULL){
                for (unsigned int x = 0; x < sheet_[i]->width(); x++){
                    for (unsigned int y = 0; y < sheet_[i]->height(); y++){
                        if(x_[i]+x < width_ && y_[i]+y < height_&& sheet_[i]->getPixel(x, y)->a != 0) {
                            *(out_->getPixel(x_[i]+x, y_[i]+y)) = *(sheet_[i]->getPixel(x, y));
                        }
                    }
                }
            }
            i++;
        }
        return *out_;
    }
 	//Renders the whole StickerSheet on one Image and returns that Image. 
}