#include "StickerSheet.h"

namespace cs225{
    void StickerSheet::_copy(StickerSheet const & other){
        delete base_;
        delete[] sheet_;// Clear self
        // Copy `other` to self

        width_ = other.width_;
        height_ = other.height_;
        max_ = other.max_;
        base_ = new Image(*(other.base_));
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

    StickerSheet::StickerSheet (const Image &picture, unsigned int max){
        width_ = picture.width();
        height_ = picture.height();
        layer_ = 0;
        *base_ = picture;
        max_ = max;
    }
 	//Initializes this StickerSheet with a base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1. 
 
 	StickerSheet::~StickerSheet (){
        delete base_;
        for (unsigned int i = 0; i < max_; i++) {
            delete sheet_[i];
        }
        delete[] sheet_;
        delete[] x_;
        delete[] y_;
    }
 	//Frees all space that was dynamically allocated by this StickerSheet. 
 
 	StickerSheet::StickerSheet (const StickerSheet &other){
        base_ = NULL;
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
        if ((layer_ < max_) && (x+sticker.width() < base_->width()) && 
            (y+sticker.height() < base_->height())) {
            *(sheet_ [layer_++]) = sticker;
            return layer_ ;
        }
        return -1;
    }
 	//Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet. 
 
    bool StickerSheet::translate (unsigned int index, unsigned int x, unsigned int y){
        if ((x <= base_->width() - sheet_[index]->width()) && 
            (y <= base_->height() - sheet_[index]->height())){
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
        return sheet_[index];
    }
 	//Returns a pointer to the sticker at the specified index, not a copy of it. 
 
    Image StickerSheet::render () const{
        Image* out;
        out = base_;
        for (unsigned int i = 0; i <= layer_; i++) {
            for (unsigned int x = 0; x < sheet_[i]->width(); x++){
                for (unsigned int y = 0; y < sheet_[i]->height(); y++){
                    *(out->getPixel(x_[i]+x, y_[i]+y)) = *(sheet_[i]->getPixel(x, y));
                }
            }
        }
        return *out;
    }
 	//Renders the whole StickerSheet on one Image and returns that Image. 
}