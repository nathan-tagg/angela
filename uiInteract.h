/*********************************************
 * Header file: INTERFACE
 * Author: Nathan Tagg
 **********************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H
#include "point.h"

/********************************************
 * INTERFACE
 ********************************************/
class Interface
{
public:
   Interface() { initialize(0, 0x0000, "Window", Point(-50, 50), Point(50, -50)); };
   Interface(int argc, char ** argv, const char * title, Point topLeft, Point bottomRight)
   {
      initialize(argc, argv, title, topLeft, bottomRight);
   }
   ~Interface();
   void run(void (*callBack)(const Interface *, void *), void *p);
   bool isTimeToDraw();
   void setNextDrawTime();
   unsigned int getNextTick() { return nextTick; };
   void setFramesPerSecond(double value);
   void keyEvent(int key, bool fDown);
   void keyEvent();
   double frameRate() const { return timePeriod;    };
   int  isDown()      const { return isDownPress;   };
   int  isUp()        const { return isUpPress;     };
   int  isLeft()      const { return isLeftPress;   };
   int  isRight()     const { return isRightPress;  };
   int  isRapid()     const { return isRapidPress;  };
   int  isShift()     const { return isShiftPress;  };
   bool isSpace()     const { return isSpacePress;  };
   bool isZ()         const { return isZPress;      };
   bool isX()         const { return isXPress;      };
   bool isC()         const { return isCPress;      };
   bool isV()         const { return isVPress;      };
   bool isB()         const { return isBPress;      };
   bool isN()         const { return isNPress;      };
   bool isM()         const { return isMPress;      };
   bool isI()         const { return isIPress;      };
   bool isT()         const { return isTPress;      };
   bool isA()         const { return isAPress;      };
   bool isS()         const { return isSPress;      };
   static void *p;                   // for client
   static void (*callBack)(const Interface *, void *);
private:
   void initialize(int argc, char ** argv, const char * title, Point topLeft, Point bottomRight);
   static bool         initialized;  // only run the constructor once!
   static double       timePeriod;   // interval between frame draws
   static unsigned int nextTick;     // time (from clock()) of our next draw
   static int  isDownPress;          // is the down arrow currently pressed?
   static int  isUpPress;            //    "   up         "
   static int  isLeftPress;          //    "   left       "
   static int  isRightPress;         //    "   right      "
   static int  isRapidPress;
   static int  isShiftPress;
   static bool isSpacePress;         //    "   space      "
   static bool isZPress;
   static bool isXPress;
   static bool isCPress;             //    "   c          "
   static bool isVPress;
   static bool isBPress;
   static bool isNPress;
   static bool isMPress;
   static bool isIPress;
   static bool isTPress;
   static bool isAPress;
   static bool isSPress;
};

/************************************************************************
 * DRAW CALLBACK
 *************************************************************************/
void drawCallback();

/************************************************************************
 * KEY DOWN CALLBACK
 *************************************************************************/
void keyDownCallback(int key, int x, int y);

/************************************************************************
 * KEY UP CALLBACK
 *************************************************************************/
void keyUpCallback(int key, int x, int y);

/***************************************************************
 * KEYBOARD CALLBACK
 ***************************************************************/
void keyboardCallback(unsigned char key, int x, int y);

/************************************************************************
 * RUN
 *************************************************************************/
void run();

#endif // UI_INTERFACE_H
