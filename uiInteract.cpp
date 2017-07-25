/***********************************************************************
 * File: INTERACT
 * Author: Nathan Tagg
 ************************************************************************/

#include <string>
#include <sstream>
#include <cassert>
#include <time.h>
#include <cstdlib>

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
#include <Gl/glut.h>
#include <ctime>
#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32

#include "uiInteract.h"
#include "point.h"
using namespace std;

/*********************************************************************
 * SLEEP
 *********************************************************************/
void sleep(unsigned long msSleep)
{
#ifdef _WIN32 // WINDOWS
   ::Sleep(msSleep + 35);
#else // LINUX, MAC
   timespec req = {};
   time_t sec = (int)(msSleep / 1000);
   msSleep -= (sec * 1000);
   req.tv_sec = sec;
   req.tv_nsec = msSleep * 1000000L;
   while (nanosleep(&req, &req) == -1);
#endif
   return;
}

/************************************************************************
 * DRAW CALLBACK
 *************************************************************************/
void drawCallback()
{
   Interface ui;
   glClear(GL_COLOR_BUFFER_BIT); //clear the screen
   glColor3f(1,1,1);
   assert(ui.callBack != NULL);
   ui.callBack(&ui, ui.p);
   if (!ui.isTimeToDraw())
      sleep((unsigned long)((ui.getNextTick() - clock()) / 1000));
   ui.setNextDrawTime();
   glutSwapBuffers();
   ui.keyEvent();
}

/************************************************************************
 * KEY DOWN CALLBACK
 *************************************************************************/
void keyDownCallback(int key, int x, int y)
{
   Interface ui;
   ui.keyEvent(key, true /*fDown*/);
}

/************************************************************************
 * KEY UP CALLBACK
 *************************************************************************/
void keyUpCallback(int key, int x, int y)
{
   Interface ui;
   ui.keyEvent(key, false /*fDown*/);
}

/***************************************************************
 * KEYBOARD CALLBACK
 ***************************************************************/
void keyboardCallback(unsigned char key, int x, int y)
{
   Interface ui;
   ui.keyEvent(key, true /*fDown*/);
}

/***************************************************************
 * INTERFACE : KEY EVENT
 ****************************************************************/
void Interface::keyEvent(int key, bool fDown)
{
   switch(key)
   {
      case GLUT_KEY_DOWN:
         isDownPress = fDown;
         break;
      case GLUT_KEY_UP:
         isUpPress = fDown;
         break;
      case GLUT_KEY_RIGHT:
         isRightPress = fDown;
         break;
      case GLUT_KEY_LEFT:
         isLeftPress = fDown;
         break;
      case GLUT_KEY_HOME:
      case ' ':
         isSpacePress = fDown;
         isRapidPress = fDown;
         break;
      case GLUT_ACTIVE_SHIFT:
         isShiftPress = fDown;
         break;
      case 'z':
         isZPress = fDown;
         break;
      case 'x':
         isXPress = fDown;
         break;
      case 'c':
         isCPress = fDown;
         break;
      case 'v':
         isVPress = fDown;
         break;
      case 'b':
         isBPress = fDown;
         break;
      case 'n':
         isNPress = fDown;
         break;
      case 'm':
         isMPress = fDown;
         break;
      case 'i':
         isIPress = fDown;
         break;
      case 't':
         isTPress = fDown;
         break;
      case 'a':
         isAPress = fDown;
         break;
      case 's':
         isSPress = fDown;
         break;
   }
}
/***************************************************************
 * INTERFACE : KEY EVENT
 ****************************************************************/
void Interface::keyEvent()
{
   if (isDownPress)
      isDownPress++;
   if (isUpPress)
      isUpPress++;
   if (isLeftPress)
      isLeftPress++;
   if (isRightPress)
      isRightPress++;
   if (isRapidPress)
      isRapidPress++;
   if (isShiftPress)
      isShiftPress++;
   isSpacePress = false;
   isZPress = false;
   isXPress = false;
   isCPress = false;
   isVPress = false;
   isBPress = false;
   isNPress = false;
   isMPress = false;
   isIPress = false;
   isTPress = false;
   isAPress = false;
   isSPress = false;
}


/************************************************************************
 * INTEFACE : IS TIME TO DRAW
 *************************************************************************/
bool Interface::isTimeToDraw()
{
   return ((unsigned int)clock() >= nextTick);
}

/************************************************************************
 * INTERFACE : SET NEXT DRAW TIME
 *************************************************************************/
void Interface::setNextDrawTime()
{
   nextTick = clock() + static_cast<int> (timePeriod * CLOCKS_PER_SEC);
}

/************************************************************************
 * INTERFACE : SET FRAMES PER SECOND
 *************************************************************************/
void Interface::setFramesPerSecond(double value)
{
    timePeriod = (1 / value);
}

/***************************************************
 * STATICS
 **************************************************/
int          Interface::isDownPress  = 0;
int          Interface::isUpPress    = 0;
int          Interface::isLeftPress  = 0;
int          Interface::isRightPress = 0;
int          Interface::isRapidPress = 0;
int          Interface::isShiftPress = 0;
bool         Interface::isSpacePress = false;
bool         Interface::isZPress =     false;
bool         Interface::isXPress =     false;
bool         Interface::isCPress =     false;
bool         Interface::isVPress =     false;
bool         Interface::isBPress =     false;
bool         Interface::isNPress =     false;
bool         Interface::isMPress =     false;
bool         Interface::isIPress =     false;
bool         Interface::isTPress =     false;
bool         Interface::isAPress =     false;
bool         Interface::isSPress =     false;
bool         Interface::initialized  = false;
double       Interface::timePeriod   = 1.0 / 120.0; // default to 30 frames/second
unsigned int Interface::nextTick     = 0;        // redraw now please
void *       Interface::p            = NULL;
void (*Interface::callBack)(const Interface *, void *) = NULL;

/************************************************************************
 * INTERFACE : DESTRUCTOR
 ***********************************************************************/
Interface::~Interface()
{
}

/************************************************************************
 * INTEFACE : INITIALIZE
 *************************************************************************/
void Interface::initialize(int argc, char ** argv, const char * title, Point topLeft, Point bottomRight)
{
   if (initialized)
      return;
   srand((long)(argv));
   glutInit(&argc, argv);
   Point point;
   glutInitWindowSize(   // size of the window
      (int)(bottomRight.getX() - topLeft.getX()),
      (int)(topLeft.getY() - bottomRight.getY()));
   glutInitWindowPosition( 10, 10);                // initial position
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // double buffering
   glutCreateWindow(title);              // text on titlebar
   glutIgnoreKeyRepeat(true);
   glClearColor(0, 0, 2, 0);          // Black is the background color
   gluOrtho2D((int)topLeft.getX(), (int)bottomRight.getX(),
              (int)bottomRight.getY(), (int)topLeft.getY()); // 2D environment
   glutDisplayFunc(   drawCallback    );
   glutIdleFunc(      drawCallback    );
   glutKeyboardFunc(  keyboardCallback);
   glutSpecialFunc(   keyDownCallback );
   glutSpecialUpFunc( keyUpCallback   );
   initialized = true;
   return;
}

/************************************************************************
 * INTERFACE : RUN
 *************************************************************************/
void Interface::run(void (*callBack)(const Interface *, void *), void *p)
{
   this->p = p;
   this->callBack = callBack;
   glutMainLoop();
   return;
}
