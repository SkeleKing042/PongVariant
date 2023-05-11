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
private:
	double distanceFromCenter;

public:
	Paddle(double speed, double width, double height, double radius, double angle);
	~Paddle();

	void MovePaddle(int inputDir);

	double GetPaddleNormal();
};