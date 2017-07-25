/***********************************************************************
 * File: DRAW
 * Author: Nathan Tagg
 ************************************************************************/

#ifndef UI_DRAW_H
#define UI_DRAW_H

#include <string>     // To display text on the screen
#include <cmath>      // for M_PI, sin() and cos()
#include "point.h"    // Where things are drawn
using std::string;

/************************************************************************
 * DRAW DIGIT
 *************************************************************************/
void drawDigit(const Point & topLeft, const char & digit);

/*************************************************************************
 * DRAW NUMBER
 *************************************************************************/
void drawNumber(const Point & topLeft, unsigned short & number);

/*************************************************************************
 * DRAW TEXT
 ************************************************************************/
void drawText(const Point & topLeft, const char * text);

/************************************************************************
 * ROTATE
 *************************************************************************/
void rotate(Point & point, const Point & origin, const short & rotation = 0);

/************************************************************************
 * DRAW LINE
 *************************************************************************/
void drawLine(const Point & begin, const Point & end, const float & red = 1.0, const float & green = 1.0, const float & blue = 1.0);

/******************************************************************
 * RANDOM
 ****************************************************************/
int  random(const int  & min, const int  & max);

/******************************************************************************
 * DRAW GROUND
 ******************************************************************************/
void drawGround();

/***********************************************************************
 * DRAW DUDE
 ***********************************************************************/
void drawDudeStanding(const Point & point);
void drawDudeCrouching(const Point & point, short & direction);
void drawDudeAirbornUp(const Point & point, short & direction);
void drawDudeAirbornDown(const Point & point, short & direction);
void drawDudeDiveBombing(const Point & point, short & direction);
//void drawPowerBar(const Point & point, short & power);

/***********************************************************************
 * DRAW PLATFORM
 ***********************************************************************/
 void drawPlatform(const Point & point, const short & width);



#endif // UI_DRAW_H
