/*************************************************************
 * Source File: GAME
 * Author: Nathan Tagg
 *************************************************************/

#include "game.h"
#include "point.h"
using namespace std;

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game()
{
	Platform * platformOne = new Platform(0, -50, 50);
	platforms.push_back(platformOne);

	Platform * platformTwo = new Platform(-300, -200, 100);
	platforms.push_back(platformTwo);

	Platform * platformThree = new Platform(100, 100, 50);
	platforms.push_back(platformThree);

	Platform * platformFour = new Platform(-100, 100, 50);
	platforms.push_back(platformFour);

	Platform * platformFive = new Platform(0, 200, 50);
	platforms.push_back(platformFive);

	Platform * ground = new Platform(0, -350, 1500);
	platforms.push_back(ground);

}

/***************************************
 * GAME DESTRUCTOR
 ***************************************/
Game :: ~Game()
{}

/**************************************
 * HANDLE INPUT
 **************************************/
void Game :: handleInput(const Interface & ui)
{
	if (ui.isUp())
		drew.up();
	if (ui.isDown())
		drew.down();
	if (ui.isRight())
		drew.right();
	if (ui.isLeft())
		drew.left();
	if (ui.isRapid())
		drew.sprint();
}

/**************************************
 *
 **************************************/
void Game :: advance()
{
	drawGround();

	drew.applyGravity(1); // change the parameter to alter gravity

	for(list<Platform*> :: iterator it = platforms.begin(); it != platforms.end(); ++it)
	{
		(*it)->advance();
		Point characterPosotion = drew.getPoint();
		Point platformPosition  = (*it)->getPoint();
		if (characterPosotion.getY() > platformPosition.getY() && characterPosotion.getY() < (platformPosition.getY() + 20)
		 && characterPosotion.getX() > (platformPosition.getX() - ((*it)->getWidth() / 2))
	   && characterPosotion.getX() < (platformPosition.getX() + ((*it)->getWidth() / 2)))
		{
			drew.land(platformPosition.getY());
		}
	}
	drew.advance();
}
