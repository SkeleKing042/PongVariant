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
	position.x = SCREENSIZE / 2 + offset;
	offset = rand() % (int)round(SCREENSIZE * STARTINGOFFSETSCALAR);
	if (offset % 2 == 0)
		offset *= -1;
	position.y = SCREENSIZE / 2 + offset;

	UpdateMoveDir(givenDir * DEG2RAD);
}

void Ball::MoveBall()
{
	// Moves the ball based on its momentum
	position.x += velocity.x * speed;
	position.y += velocity.y * speed;		
}
void Ball::UpdateMoveDir(double newAngle)
{
	//Set the movement direction to the given angle and update the velocity of the ball
	moveDir = newAngle;
	velocity.x = cos(moveDir);
	velocity.y = sin(moveDir);
}