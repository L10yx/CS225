#include "StickerSheet.h"

using namespace cs225;

int main() {
  Image pic;
  pic.readFromFile("alma.png");

  pic.writeToFile("myImage.png");
  return 0;
}
