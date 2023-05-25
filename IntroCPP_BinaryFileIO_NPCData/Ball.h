#pragma once
#include "raylib.h"
#include <vector>
/// <summary>
/// The ball that can bounce of the paddle
/// </summary>
class Ball
{
public:
	Vector2 _position;
	Vector2 _velocity;
	double _moveDir = 0;
	double _speed = 0;
	double _size = 0;
	bool _collidable = true;
	Color _color;
public:
	/// <summary>
/// Ball contructor
/// </summary>
	Ball();
	/// <summary>
/// Ball destructor
/// </summary>
	~Ball();
	/// <summary>
/// Ball initalisation
/// </summary>
/// <param name="Given Speed"></param>
/// <param name="Given Size"></param>
/// <param name="Given Direction"></param>
/// <param name="Given Color"></param>
	void Init(double GivenSpeed, double GivenSize, double GivenDirection, Color GivenColor);
	/// <summary>
/// Moves the ball based on its momentum
/// </summary>
/// <param name="Scale"></param>
	void MoveBall(double Scale);
	/// <summary>
///Set the movement direction to the given angle and update the velocity of the ball
/// </summary>
/// <param name="New Angle"></param>
	void UpdateMoveDir(double NewAngle);
	/// <summary>
/// Draws the ball
/// </summary>
	void Draw();
};