#include "StickerSheet.h"

using namespace cs225;

int main() {
  Image pic;
  pic.readFromFile("alma.png");
  StickerSheet mypic(pic, 3);
  pic.readFromFile("i.png");
  pic.scale(1.5);
  
  mypic.addSticker(pic, 15, 15);
  mypic.addSticker(pic, 125, 10);
  mypic.addSticker(pic, 225, 5);
  pic = mypic.render();
  
  pic.writeToFile("myImage.png");
  return 0;
}
