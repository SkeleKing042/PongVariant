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

public:
	Paddle(double givenSpeed, double givenWidth, double givenHeight);
	~Paddle();

	void MovePaddle(int inputDir);
};