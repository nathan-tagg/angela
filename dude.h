#ifndef DUDE_H
#define DUDE_H

#include <math.h>
#include "uiDraw.h"
#include "point.h"
#include "velocity.h"
#include "uiInteract.h"

class Dude
{
private:
	Point point;
	Velocity velocity;
	int action; // Code for all different Animations and flipbooks.
	int charge;
	short facing; // Whitch way is he facing. Right = 1, left = -1.
	int jump;

public:
	Dude()
	{
		action = 0; // STANDING
		charge = 0;
		facing = 1; // Start facing right.
		point.setX(0);
		point.setY(0);
		velocity.setDX(0);
		velocity.setDY(0);
		jump = 6;
	}

	void left()
	{ point.addX(-7); facing = -1; }

	void right()
	{ point.addX( 7); facing =  1; }

	void up() // Hold to charge JUMP
	{
		if (jump) { velocity.setDY(20); jump--; }
	}

	void down()
	{
		action = 1; // CROUCHING
	}

	void sprint()
	{
		point.addX(facing * 3);
	}

	void draw()
	{
		if (action == 0) // STANDING
		{ drawDudeStanding(point); }
		if (action == 1) // CROUCHING
		{ drawDudeCrouching(point, facing); }
		if (action == 3) // AIRBORN - UP
		{ drawDudeAirbornUp(point, facing); }
		if (action == 4) // AIRBORN - DOWN
		{ drawDudeAirbornDown(point, facing); }
	}

	void applyGravity(int gravity)
	{ if (velocity.getDY() > -19) velocity.addDY(-gravity);
	 	if (velocity.getDY() < -19) velocity.setDY(-19);}

	void advance()
	{
		point.addX(velocity.getDX());
		point.addY(velocity.getDY());

		if (velocity.getDY() > 0) { action = 3; } //AIRBORN - UP
		if (velocity.getDY() < 0) { action = 4; } //AIRBORN - DOWN

		//if (charge && action != 1) { velocity.setDY(charge); charge = 0;} // JUMP

		if (point.getX() > 655 || point.getX() < -655) { point.setX(-point.getX()); } // WRAPPING, TAKE THIS OUT FOR SIDE SCROLLING
		if (point.getY() > 655 || point.getY() < -655) { point.setY(-point.getY()); } // WRAPPING, TAKE THIS OUT FOR SIDE SCROLLING

		draw();

	}

	void land(int height)
	{
		if (velocity.getDY() <= 0)
		{
			velocity.setDY(0); point.setY(height + 15); jump = 6; action = 0;
		}
	}

	Point getPoint() const { return point; }

	int fallingSpeed() { unsigned int speed = velocity.getDY(); return speed; }

};

#endif
