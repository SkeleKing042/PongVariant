#include "Ball.h"
#include "GameDefines.h"
/// <summary>
/// Ball contructor
/// </summary>
Ball::Ball()
{
	_collidable = true;
	_position.x = _position.y = _velocity.x = _velocity.y = 0;
}
/// <summary>
/// Ball destructor
/// </summary>
Ball::~Ball() { }
/// <summary>
/// Ball initalisation
/// </summary>
/// <param name="Given Speed"></param>
/// <param name="Given Size"></param>
/// <param name="Given Direction"></param>
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
/// <summary>
/// Moves the ball based on its momentum
/// </summary>
/// <param name="Scale"></param>
void Ball::MoveBall(double s)
{
	_position.x += _velocity.x * (float)_speed * (float)s;
	_position.y += _velocity.y * (float)_speed * (float)s;
}
/// <summary>
///Set the movement direction to the given angle and update the velocity of the ball
/// </summary>
/// <param name="New Angle"></param>
void Ball::UpdateMoveDir(double newAngle)
{
	_moveDir = newAngle;
	_velocity.x = (float)cos(_moveDir);
	_velocity.y = (float)sin(_moveDir);
}
/// <summary>
/// Draws the ball
/// </summary>
void Ball::Draw()
{
	DrawCircleV(_position, (float)_size, BALLCOLOUR);
}