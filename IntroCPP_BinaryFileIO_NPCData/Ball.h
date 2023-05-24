#pragma once

#include "raylib.h"
#include <vector>

class Ball
{
public:
	Vector2 _position;
	Vector2 _velocity;
	double _moveDir = 0;
	double _speed = 0;
	double _size = 0;
	bool _collidable = true;

public:
	Ball();
	~Ball();

	void Init(double givenSpeed, double givenSize, double givenDir);

	void MoveBall(double scale);
	void UpdateMoveDir(double newAngle);
	void Draw();
};