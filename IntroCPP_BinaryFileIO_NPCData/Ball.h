#pragma once

#include "raylib.h"
#include <vector>

using namespace std;

class Ball
{
public:
	Vector2 position;
	Vector2 velocity;
	double moveDir = 0;
	double speed = 0;
	double size = 0;
	bool collidable = true;

public:
	Ball();
	~Ball();

	void Init(double givenSpeed, double givenSize, double givenDir);

	void MoveBall(double scale);
	void UpdateMoveDir(double newAngle);
	void Draw();
};