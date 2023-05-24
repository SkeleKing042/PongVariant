#include "Ball.h"
#include "raylib.h"
#include <iostream>
#include <conio.h>
#include <dos.h>
#include "GameDefines.h"

Ball::Ball()
{
	_collidable = true;
	_position.x = _position.y = _velocity.x = _velocity.y = 0;
}

Ball::~Ball() { }

void Ball::Init(double givenSpeed, double givenSize, double givenDir)
{
	// Ball setup
	_collidable = true;
	_speed = givenSpeed;
	_size = givenSize;

	//Generates a random int based off the screen size and use it to give the ball a random start
	//point each game
	int offset = rand() % (int)round(SCREENSIZE * STARTINGOFFSETSCALAR);
	if (offset % 2 == 0)
		offset *= -1;
	_position.x = (float)SCREENSIZE / 2 + (float)offset;
	offset = rand() % (int)round(SCREENSIZE * STARTINGOFFSETSCALAR);
	if (offset % 2 == 0)
		offset *= -1;
	_position.y = (float)SCREENSIZE / 2 + (float)offset;

	UpdateMoveDir(givenDir * DEG2RAD);
}

void Ball::MoveBall(double s)
{
	// Moves the ball based on its momentum
	_position.x += _velocity.x * (float)_speed * (float)s;
	_position.y += _velocity.y * (float)_speed * (float)s;
}
void Ball::UpdateMoveDir(double newAngle)
{
	//Set the movement direction to the given angle and update the velocity of the ball
	_moveDir = newAngle;
	_velocity.x = (float)cos(_moveDir);
	_velocity.y = (float)sin(_moveDir);
}

void Ball::Draw()
{
	DrawCircleV(_position, (float)_size, BALLCOLOUR);
}