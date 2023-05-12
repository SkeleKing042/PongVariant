#include "Ball.h"
#include "raylib.h"
#include <iostream>
#include <conio.h>
#include <dos.h>
#include "GameDefines.h"
using namespace std;

Ball::Ball(double givenSpeed, double givenSize, double giveDir)
{
	collidable = true;
	speed = givenSpeed;
	size = givenSize;

	//Generates a random int based off the screen size and use it to give the ball a random start
	//point each game
	int offset = rand() % (int)round(SCREENSIZE * STARTINGOFFSETSCALAR);
	if (offset % 2 == 0)
		offset *= -1;
	position.x = SCREENSIZE / 2 + offset;
	offset = rand() % (int)round(SCREENSIZE * STARTINGOFFSETSCALAR);
	if (offset % 2 == 0)
		offset *= -1;
	position.y = SCREENSIZE / 2 + offset;

	UpdateMoveDir(giveDir * DEG2RAD);
}

Ball::~Ball()
{

}

void Ball::MoveBall()
{
	// Moves the ball based on its momentum
	position.x += velocity.x * speed;
	position.y += velocity.y * speed;

	//Close game upon ball hiting wall
	//Scales with ball size
	if (position.x <= 0 + size || position.x >= SCREENSIZE - size || position.y <= 0 + size || position.y >= SCREENSIZE - size)
		exit(420);
}
void Ball::UpdateMoveDir(double newAngle)
{
	//Set the movement direction to the given angle and update the velocity of the ball
	moveDir = newAngle;
	velocity.x = cos(moveDir);
	velocity.y = sin(moveDir);
}