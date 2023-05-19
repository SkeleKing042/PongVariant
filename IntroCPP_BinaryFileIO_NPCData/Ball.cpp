#include "Ball.h"
#include "raylib.h"
#include <iostream>
#include <conio.h>
#include <dos.h>
#include "GameDefines.h"
using namespace std;

Ball::Ball()
{
	collidable = true;
	position.x = position.y = velocity.x = velocity.y = 0;
}

Ball::~Ball() { }

void Ball::Init(double givenSpeed, double givenSize, double givenDir)
{
	// Ball setup
	collidable = true;
	speed = givenSpeed;
	size = givenSize;

	//Generates a random int based off the screen size and use it to give the ball a random start
	//point each game
	int offset = rand() % (int)round(SCREENSIZE * STARTINGOFFSETSCALAR);
	if (offset % 2 == 0)
		offset *= -1;
	position.x = (float)SCREENSIZE / 2 + (float)offset;
	offset = rand() % (int)round(SCREENSIZE * STARTINGOFFSETSCALAR);
	if (offset % 2 == 0)
		offset *= -1;
	position.y = (float)SCREENSIZE / 2 + (float)offset;

	UpdateMoveDir(givenDir * DEG2RAD);
}

void Ball::MoveBall(double s)
{
	// Moves the ball based on its momentum
	position.x += velocity.x * (float)speed * (float)s;
	position.y += velocity.y * (float)speed * (float)s;
}
void Ball::UpdateMoveDir(double newAngle)
{
	//Set the movement direction to the given angle and update the velocity of the ball
	moveDir = newAngle;
	velocity.x = (float)cos(moveDir);
	velocity.y = (float)sin(moveDir);
}

void Ball::Draw()
{
	DrawCircleV(position, (float)size, BALLCOLOUR);
}