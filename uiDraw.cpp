 /***********************************************************************
 * Source File: DRAW
 * Author: Nathan Tagg
 ************************************************************************/

#include <string>
#include <sstream>
#include <cassert>
#include <time.h>

#ifdef __APPLE__
#include <openGL/gl.h>
#include <GLUT/glut.h>
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>
#include <GL/glut.h>
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32

#include "point.h"
#include "uiDraw.h"
#include <vector>

using namespace std;

#define deg2rad(value) ((M_PI / 180) * (value))

/*********************************************
 * NUMBER OUTLINES
 ********************************************/
const char NUMBER_OUTLINES[10][20] =
{
   {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   0,10,  0, 0,  -1,-1, -1,-1},//0
   {7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//1
   {0, 0,  7, 0,   7, 0,  7, 5,   7, 5,  0, 5,   0, 5,  0,10,   0,10,  7,10},//2
   {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   4, 5,  7, 5,  -1,-1, -1,-1},//3
   {0, 0,  0, 5,   0, 5,  7, 5,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1},//4
   {7, 0,  0, 0,   0, 0,  0, 5,   0, 5,  7, 5,   7, 5,  7,10,   7,10,  0,10},//5
   {7, 0,  0, 0,   0, 0,  0,10,   0,10,  7,10,   7,10,  7, 5,   7, 5,  0, 5},//6
   {0, 0,  7, 0,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//7
   {0, 0,  7, 0,   0, 5,  7, 5,   0,10,  7,10,   0, 0,  0,10,   7, 0,  7,10},//8
   {0, 0,  7, 0,   7, 0,  7,10,   0, 0,  0, 5,   0, 5,  7, 5,  -1,-1, -1,-1} //9
};

/************************************************************************
 * DRAW DIGIT
 *************************************************************************/
void drawDigit(const Point & topLeft, const char & digit)
{
   assert(isdigit(digit));
   if (!isdigit(digit))
      return;
   short r = digit - '0';
   assert(r >= 0 && r <= 9);
   for (int c = 0; c < 20 && NUMBER_OUTLINES[r][c] != -1; c += 4)
   {
      assert(NUMBER_OUTLINES[r][c    ] != -1 &&
             NUMBER_OUTLINES[r][c + 1] != -1 &&
             NUMBER_OUTLINES[r][c + 2] != -1 &&
             NUMBER_OUTLINES[r][c + 3] != -1);
      Point start;
      start.setX(topLeft.getX() + NUMBER_OUTLINES[r][c]);
      start.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 1]);
      Point end;
      end.setX(topLeft.getX() + NUMBER_OUTLINES[r][c + 2]);
      end.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 3]);
      drawLine(start, end);
   }
}

/*************************************************************************
 * DRAW NUMBER
 *************************************************************************/
void drawNumber(const Point & topLeft, unsigned short & number)
{
   Point point = topLeft;
   bool isNegative = (number < 0);
   number *= (isNegative ? -1 : 1);
   ostringstream sout;
   sout << number;
   string text = sout.str();
   if (isNegative)
   {
      glBegin(GL_LINES);
      glVertex2f(point.getX() + 1, point.getY() - 5);
      glVertex2f(point.getX() + 5, point.getY() - 5);
      glEnd();
      point.addX(11);
   }
   for (const char *p = text.c_str(); *p; p++)
   {
      assert(isdigit(*p));
      drawDigit(point, *p);
      point.addX(11);
   }
}

/*************************************************************************
 * DRAW TEXT
 ************************************************************************/
void drawText(const Point & topLeft, const char * text)
{
   void *pFont = GLUT_BITMAP_HELVETICA_12;  // also try _18
   glRasterPos2f(topLeft.getX(), topLeft.getY());
   for (const char *p = text; *p; p++)
      glutBitmapCharacter(pFont, *p);
}

/************************************************************************
 * ROTATE
 *************************************************************************/
void rotate(Point & point, const Point & origin, const short & rotation)
{
   double cosA = cos(deg2rad(rotation));
   double sinA = sin(deg2rad(rotation));
   Point tmp(false /*check*/);
   tmp.setX(point.getX() - origin.getX());
   tmp.setY(point.getY() - origin.getY());
   point.setX(static_cast<int> (tmp.getX() * cosA -
                                tmp.getY() * sinA) +
              origin.getX());
   point.setY(static_cast<int> (tmp.getX() * sinA +
                                tmp.getY() * cosA) +
              origin.getY());
}

/************************************************************************
 * DRAW LINE
 *************************************************************************/
void drawLine(const Point & begin, const Point & end, const float & red, const float & green, const float & blue)
{
   glBegin(GL_LINES);
   glColor3f(red, green, blue);
   glVertex2f(begin.getX(), begin.getY());
   glVertex2f(  end.getX(),   end.getY());
   glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
   glEnd();
}

/****************************************************************
 * RANDOM
 ****************************************************************/
int random(const int & min, const int & max)
{
   assert(min <= max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);
   return num;
}

/****************************************************************
 * DRAW GROUND
 ****************************************************************/
void drawGround()
{
	for(int i = -350; i > -400; i--)
	{
		Point begin(-650, i);
		Point end(650, i);
		drawLine(begin, end, .3, .7, 0);
	}
}

void drawPlatform(const Point & point, const short & width)
{
   for(int i = (point.getX() - (width / 2)); i < point.getX() + (width / 2); i++)
   {
      Point begin(i, point.getY());
      Point end(i, point.getY() - 5);
      drawLine(begin, end);
   }
};

/****************************************************************
 * DRAW DUDE STANDING
 ****************************************************************/
void drawDudeStanding(const Point & point)
{
   struct PT
   {
      short x;
      short y;
   };
   PT legs[] =
   {
      {10, -15}, {0, 0}, {-10, -15}
   };
   PT body[] =
   {
      {0, 0}, {0, 20}
   };
   PT arms[] =
   {
      {10, 0}, {0, 15}, {-10, 0}
   };
   PT head[] =
   {
      {5, 20}, {-5, 20}, {-5, 30}, {5, 30}, {5, 20}
   };
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 3; i++)
   {
      glVertex2f(point.getX() + legs[i].x, point.getY() + legs[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 2; i++)
   {
      glVertex2f(point.getX() + body[i].x, point.getY() + body[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 3; i++)
   {
      glVertex2f(point.getX() + arms[i].x, point.getY() + arms[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 5; i++)
   {
      glVertex2f(point.getX() + head[i].x, point.getY() + head[i].y);
   }
   glEnd();
   
}

/****************************************************************
 * DRAW DUDE CROUCHING
 ****************************************************************/
void drawDudeCrouching(const Point & point, short & direction)
{
   struct PT
   {
      short x;
      short y;
   };
   PT legs[] =
   {
      {15, -15}, {15, -5}, {-10, -15}
   };
   PT body[] =
   {
      {0, -11}, {5, 5}
   };
   PT arms[] =
   {
      {-10, 5}, {10, 0}, {5, -5}
   };
   PT head[] =
   {
      {0, 5}, {10, 5}, {10, 15}, {0, 15}, {0, 5}
   };
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 3; i++)
   {
      glVertex2f(point.getX() + direction * legs[i].x, point.getY() + legs[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 2; i++)
   {
      glVertex2f(point.getX() + direction * body[i].x, point.getY() + body[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 3; i++)
   {
      glVertex2f(point.getX() + direction * arms[i].x, point.getY() + arms[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 5; i++)
   {
      glVertex2f(point.getX() + direction * head[i].x, point.getY() + head[i].y);
   }
   glEnd();
}

/****************************************************************
 * DRAW DUDE AIRBORN UP
 ****************************************************************/
void drawDudeAirbornUp(const Point & point, short & direction)
{
   struct PT
   {
      short x;
      short y;
   };
   PT legs[] =
   {
      {10, 0}, {10, 10}, {-10, -15}
   };
   PT body[] =
   {
      {0, -2}, {5, 18}
   };
   PT arms[] =
   {
      {15, 18}, {-5, 5}, {0, 15}
   };
   PT head[] =
   {
      {0, 18}, {10, 18}, {10, 28}, {0, 28}, {0, 18}
   };
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 3; i++)
   {
      glVertex2f(point.getX() + direction * legs[i].x, point.getY() + legs[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 2; i++)
   {
      glVertex2f(point.getX() + direction * body[i].x, point.getY() + body[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 3; i++)
   {
      glVertex2f(point.getX() + direction * arms[i].x, point.getY() + arms[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 5; i++)
   {
      glVertex2f(point.getX() + direction * head[i].x, point.getY() + head[i].y);
   }
   glEnd();
}

/****************************************************************
 * DRAW DUDE AIRBORN DOWN
 ****************************************************************/
void drawDudeAirbornDown(const Point & point, short & direction)
{
   struct PT
   {
      short x;
      short y;
   };
   PT legs[] =
   {
      {5, -15}, {0, 0}, {7, 10}, {5, -5}
   };
   PT body[] =
   {
      {0, 0}, {0, 20}
   };
   PT arms[] =
   {
      {-7, 5}, {-7, 10}, {13, 20}
   };
   PT head[] =
   {
      {5, 20}, {-5, 20}, {-5, 30}, {5, 30}, {5, 20}
   };
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 4; i++)
   {
      glVertex2f(point.getX() + direction * legs[i].x, point.getY() + legs[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 2; i++)
   {
      glVertex2f(point.getX() + direction * body[i].x, point.getY() + body[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 3; i++)
   {
      glVertex2f(point.getX() + direction * arms[i].x, point.getY() + arms[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 5; i++)
   {
      glVertex2f(point.getX() + direction * head[i].x, point.getY() + head[i].y);
   }
   glEnd();
}

/****************************************************************
 * DRAW DUDE DIVE BOMBING
 ****************************************************************/
void drawDudeDiveBombing(const Point & point, short & direction)
{
   struct PT
   {
      short x;
      short y;
   };
   PT legs[] =
   {
      {0, 0}, {7, -10}, {0, -5}
   };
   PT body[] =
   {
      {0, 0}, {5, 18}
   };
   PT arms[] =
   {
      {-5, 10}, {-7, 17}, {13, 10}
   };
   PT head[] =
   {
      {0, 18}, {10, 18}, {10, 28}, {0, 28}, {0, 18}
   };
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 3; i++)
   {
      glVertex2f(point.getX() + direction * legs[i].x, point.getY() + legs[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 2; i++)
   {
      glVertex2f(point.getX() + direction * body[i].x, point.getY() + body[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 3; i++)
   {
      glVertex2f(point.getX() + direction * arms[i].x, point.getY() + arms[i].y);
   }
   glEnd();
   glBegin(GL_LINE_STRIP);
   for (short i = 0; i < 5; i++)
   {
      glVertex2f(point.getX() + direction * head[i].x, point.getY() + head[i].y);
   }
   glEnd();
}


/******************
 * DRAW POWER BAR
 ******************/
//void drawPowerBar(const Point & point, short & power)
//{
//   for (short i = 0; i < 5; i++)
//   {
//      Point start(point.getX() - 20, point.getY() + 20 + i);
//      Point end(point.getX() - 20 + power, point.getY() + 20 + i);
//      drawLine(start, end);
//   }
//}
