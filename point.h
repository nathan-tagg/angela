/***********************************************************************
 * Header File: POINT
 * Author: Nathan Tagg
 ************************************************************************/

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <math.h>

/*********************************************
 * POINT
 * A single position.  
 *********************************************/
class Point
{
public:
   Point()            : x(0.0), y(0.0)  {}
   Point(bool check)  : x(0.0), y(0.0)  {}
   Point(float x, float y);
   float getX()       const { return x;              }
   float getY()       const { return y;              }
   void setX(float x);
   void setY(float y);
   void addX(float dx)      { setX(getX() + dx);     }
   void addY(float dy)      { setY(getY() + dy);     }
   friend short operator - (const Point & lhs, const Point & rhs)    // non - member friend
   {
      short distance = (sqrtf((lhs.getX() - rhs.getX()) * (lhs.getX() - rhs.getX()) + (lhs.getY() - rhs.getY()) * (lhs.getY() - rhs.getY())));
      return distance;  // returns the distance between the two points
   }
private:
   float x;           // horizontal position
   float y;           // vertical position
};
std::ostream & operator << (std::ostream & out, const Point & pt);
std::istream & operator >> (std::istream & in,        Point & pt);

#endif // POINT_H
