#pragma once

#include "raylib.h"
#include <vector>

using namespace std;

class Ball
{
public:
	Vector2 position;
	Vector2 velocity;
	double moveDir;
	double speed;
	double size;
	bool collidable;

public:
	Ball();
	~Ball();

	void Init(double givenSpeed, double givenSize, double givenDir);

	void MoveBall();
	void UpdateMoveDir(double newAngle);
};