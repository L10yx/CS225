#include "StickerSheet.h"


namespace cs225{
    void StickerSheet::_copy(StickerSheet const & other){
        delete base_;
        delete out_;
        for (unsigned int i = 0; i < max_; i++) {
            delete sheet_[i];
            sheet_[i] = nullptr;
        }
        delete[] sheet_;
        sheet_ = nullptr;
        delete[] x_;
        x_ = nullptr;
        delete[] y_;
        y_ = nullptr;
        // Clear self
        // Copy `other` to self

        width_ = other.width_;
        height_ = other.height_;
        max_ = other.max_;
        layer_ = other.layer_;
        base_ = new Image(*other.base_);
        out_ = new Image(*other.base_);
        sheet_ = new Image*[max_];
        x_ = new unsigned int[max_];
        y_ = new unsigned int[max_];

        for (unsigned int i = 0; i < max_; i++) {
            if (other.sheet_[i] != nullptr) sheet_[i] = new Image(*other.sheet_[i]);
            else  sheet_[i] = nullptr;
            x_[i] = other.x_[i];
            y_[i] = other.y_[i];
        }
    }
    //Copeies the contents of `other` to self

    StickerSheet::StickerSheet () {
        Image* pic = new Image(100,100);
        StickerSheet(*pic, 1);
        delete pic;
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
            sheet_[i] = nullptr;
        }        
    }
 	//Initializes this StickerSheet with a base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1. 
 
 	StickerSheet::~StickerSheet (){
        delete base_;
        delete out_;
        for (unsigned int i = 0; i < max_; i++) {
            delete sheet_[i];
            sheet_[i] = nullptr;
        }
        delete[] sheet_;
        sheet_ = nullptr;
        delete[] x_;
        x_ = nullptr;
        delete[] y_;
        y_ = nullptr;
    }
 	//Frees all space that was dynamically allocated by this StickerSheet. 
 
 	StickerSheet::StickerSheet (const StickerSheet &other){
        max_ = 0;
        layer_ = 0;
        width_ = 0;
        height_ = 0;
        base_ = nullptr;
        out_ = nullptr;
        sheet_ = nullptr;
        x_ = nullptr;
        y_ = nullptr;
        _copy(other);
    }
 	//The copy constructor makes this StickerSheet an independent copy of the source. 
 
    const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
        if (this != &other) { _copy(other); }
        return *this;
    }
 	//The assignment operator for the StickerSheet class. 
 
    void StickerSheet::changeMaxStickers (unsigned int max){
        if (layer_ >= max) layer_ = max-1;
        Image **tempsheet = new Image*[max];
        unsigned int *tempx = new unsigned int[max];
        unsigned int *tempy = new unsigned int[max];
        for (unsigned int i = 0; i < max; i++) {
            if ( i < max_ && sheet_[i] != nullptr){
                tempsheet[i] = new Image(*sheet_[i]);
                tempx[i] = x_[i];
                tempy[i] = y_[i];
            }
            else{
                tempsheet[i] = nullptr;
                tempx[i] = 0;
                tempy[i] = 0;
            }
        }
        for (unsigned int i = 0; i < max_; i++) {
            delete sheet_[i];
            sheet_[i] = nullptr;
        }
        delete[] sheet_;
        sheet_ = tempsheet;
        delete[] x_;
        x_ = tempx;
        delete[] y_;
        y_ = tempy;
        max_ = max;
    }
 	//Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices. 
 
    int StickerSheet::addSticker (Image &sticker, unsigned int x, unsigned int y){
        for(unsigned int i = 0; i <= layer_; i++){
            if (sheet_[i] == NULL) {
                sheet_[i] = new Image(sticker);
                x_[i] = x;
                y_[i] = y;
                return i;
            }
        }
        if ( layer_ < max_-1)  {
            layer_++;
            sheet_ [layer_] = new Image(sticker);
            x_[layer_] = x;
            y_[layer_] = y;
            return layer_ ;
        }
        return -1;
    }
 	//Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet. 
 
    bool StickerSheet::translate (unsigned int index, unsigned int x, unsigned int y){
        if (index < max_ && sheet_[index] != NULL){
            x_ [index] = x;
            y_ [index] = y;
            return true;
        }
        return false;
    }
 	//Changes the x and y coordinates of the Image in the specified layer. 
 
    void StickerSheet::removeSticker (unsigned int index){
        if (index >= max_) return;
        delete sheet_[index];
        sheet_[index] = nullptr;
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
        unsigned int w = width_;
        unsigned int h = height_;
        while( i < max_ ) {
            if(sheet_[i] != NULL){
                if(x_[i]+sheet_[i]->width() > w) w = x_[i]+sheet_[i]->width();
                if(y_[i]+sheet_[i]->height() > h) h = y_[i]+sheet_[i]->height();
                out_->resize(w, h);
                for (unsigned int x = 0; x < sheet_[i]->width(); x++){
                    for (unsigned int y = 0; y < sheet_[i]->height(); y++){
                        if(sheet_[i]->getPixel(x, y)->a != 0) {
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