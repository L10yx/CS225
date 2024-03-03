
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png;      png.readFromFile("tests/pacman.png");

  FloodFilledImage image(png);
  BFS bfs(png, Point(100, 38), 0.4);
  HSLAPixel color(175, 1, 0.5);
  MyColorPicker my(color, Point(100, 40), 130);
  image.addFloodFill(bfs, my);
  Animation animation = image.animate(1000);
  image.animate(1000);
  BFS bfs2(png, Point(100, 30), 0.4);
  HSLAPixel color2(20, 1, 0.5);
  MyColorPicker my2(color2, Point(100, 30), 200);
  image.addFloodFill(bfs2, my2);
  Animation animation2 = image.animate(1000);
  for(unsigned int i = 0; i < animation2.frameCount(); i++) {
    animation.addFrame(animation2.getFrame(i));
  }

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  

  return 0;
}
