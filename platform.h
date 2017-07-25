#ifndef PLATFORM_H
#define PLATFORM_H

#include "point.h"
#include "uiDraw.h"

class Platform
{
private:
  Point point;
  int width;
public:
  Platform() { }
  Platform(int x, int y, int w) { point.setX(x); point.setY(y); width = w; }
  float height() { return point.getY(); }
  void draw()
  {
    drawPlatform(point, width);
  }
  void advance()
  { draw(); }
  Point getPoint() const { return point; }
  int getWidth() const { return width; }
};

#endif
