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

public:
	Ball(double givenSpeed, double givenSize, double givenDir);
	~Ball();

	void MoveBall();
	void UpdateMoveDir(double newAngle);
	double GetMovementDir();
};