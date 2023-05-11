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
	position.x = GetScreenWidth() / 2;
	position.y = GetScreenHeight() / 2;
	moveDir = giveDir * DEG2RAD;
	velocity.x = cos(moveDir);
	velocity.y = sin(moveDir);
	//momentum.push_back(givenMomentum[0] * speed);
	//momentum.push_back(givenMomentum[1] * speed);
}

Ball::~Ball()
{

}

void Ball::MoveBall()
{
	// Moves the ball based on its momentum
	position.x += velocity.x * speed;
	position.y += velocity.y * speed;

	// Screen edge detection
	// Scales with ball size
	// Needs to be changed to fit new moveDir stuff
	if (position.x <= 0 + size || position.x >= GetScreenWidth() - size || position.y <= 0 + size || position.y >= GetScreenHeight() - size)
	{
		exit(0);
	}

}
void Ball::UpdateMoveDir(double newAngle)
{
	moveDir = newAngle;
	velocity.x = cos(moveDir);
	velocity.y = sin(moveDir);
}
double Ball::GetMovementDir()
{
	//cout << "x Dir: " << 90 * momentum[0] << " | y Dir: " << 
	return 0;
}
void Ball::CollisionsFlipSwitch()
{
}