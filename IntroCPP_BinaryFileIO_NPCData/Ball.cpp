#include "Ball.h"
#include "raylib.h"
#include <iostream>
#include <conio.h>
#include <dos.h>
using namespace std;

Ball::Ball(double givenSpeed, double givenSize, double giveDir)
{
	collidable = true;
	speed = givenSpeed;
	size = givenSize;
	position.x = 150;
	position.y = 150;
	moveDir = giveDir * DEG2RAD;
	velocity.x = cos(moveDir);
	velocity.y = sin(moveDir);
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
	if (position.x <= 0 + size || position.x >= GetScreenWidth() - size || position.y <= 0 + size || position.y >= GetScreenHeight() - size)
		exit(420);
}
void Ball::UpdateMoveDir(double newAngle)
{
	//Set the movement direction to the given angle and update the velocity of the ball
	moveDir = newAngle;
	velocity.x = cos(moveDir);
	velocity.y = sin(moveDir);
}