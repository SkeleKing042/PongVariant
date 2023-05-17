#pragma once

#include "raylib.h"
#include <vector>

using namespace std;

class Paddle
{
public:
	double angle;
	double speed = 1.0;
	pair<double, double> size;
	Rectangle rec;
	Vector2 recCenter;
	double distanceFromCenter;

	pair<pair<Vector2, Vector2>, pair<Vector2, Vector2>> corners;

public:
	Paddle();
	~Paddle();

	void Init(double speed, double width, double height, double radius, double angle);

	void MovePaddle(int inputDir);

	void SetCorners();
};