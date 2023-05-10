#include "Ball.h"
#include "raylib.h"
#include <iostream>

using namespace std;

// circle goes
// 0   = -y =x
// 45  = -y +x
// 90  = =y +x
// 135 = +y +x
// 180 = +y =x
// 225 = +y -x
// 270 = =y -x
// 315 = -y -x
// 360 = -y =x
Ball::Ball(double givenSpeed, double givenSize, double giveDir)
{
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
	if (position.x <= 0 + size || position.x >= GetScreenWidth() - size)
	{
		velocity.x *= -1;
	}
	if (position.y <= 0 + size || position.y >= GetScreenHeight() - size)
	{
		velocity.y *= -1;
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