/*****************************************************
 * File: Driver.cpp
 * Author: Nathan Tagg
 *****************************************************/
#include "game.h"
#include "uiInteract.h"

/*****************************************************
 * CALL BACK: This is the Loop.
 *****************************************************/
void callBack(const Interface *pUI, void *p)
{
   Game *pGame = (Game *)p; 
   pGame->advance();
   pGame->handleInput(*pUI);
}

/*****************************************************
 * MAIN: Main ties everything together and sets up the environment.
 *****************************************************/
int main(int argc, char ** argv)
{
   Point topLeft(-650, 400);
   Point bottomRight(650, -400);
   Interface ui(argc, argv, "Angela", topLeft, bottomRight);
   Game game;
   ui.run(callBack, &game);
   return 0;
}
