#pragma once
#include "raylib.h"
#include <vector>
/// <summary>
/// The paddle that the ball object can bounce off of
/// </summary>
class Paddle
{
public:
	//[0] = angle value
	//[1] = offset
	double _angle[2] = {0, 0};
	double _speed = 1.0;
	Rectangle _rec;
	Vector2 _recCenter;
	Vector2 _position;
	double _distanceFromCenter;
	std::pair<std::pair<Vector2, Vector2>, std::pair<Vector2, Vector2>> _corners;
public:
	/// <summary>
/// Paddle constructor
/// </summary>
	Paddle();
	/// <summary>
/// Paddle destructor
/// </summary>
	~Paddle();
	/// <summary>
/// Paddle initalisation
/// </summary>
/// <param name="Speed"></param>
/// <param name="Width"></param>
/// <param name="Height"></param>
/// <param name="Radius"></param>
/// <param name="Angle"></param>
	void Init(double Speed, double Width, double Height, double Radius, double Angle);
	/// <summary>
/// Moves the paddle around the angle point
/// </summary>
/// <param name="Input Direction"></param>
/// <param name="Scale"></param>
	void MovePaddle(int InputDir, double Scale);
	/// <summary>
/// Finds the corners of the player paddle and saves them to a pair of a pair of Vector2s variable
/// </summary>
	void SetCorners();
	/// <summary>
/// Draws the paddle
/// </summary>
	void Draw();
};