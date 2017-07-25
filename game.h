/*************************************************************
 * Header File: game.h
 * Author: Nathan Tagg
 *************************************************************/

#ifndef GAME_H
#define GAME_H

#include "uiInteract.h"
#include "uiDraw.h"
#include "point.h"
#include "dude.h"
#include "platform.h"

#include <list>

/*****************************************
 * GAME
 *****************************************/
class Game
{
public:
  Game();
  ~Game();
  void handleInput(const Interface & ui);
  void advance();

private:
  Dude drew;
  std::list<Platform*> platforms;
};

#endif /* GAME_H */
