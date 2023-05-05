#pragma once

#include "raylib.h"
#include <vector>

using namespace std;

class Ball
{
public:
	vector<double> position;
	vector<double> momentum;
	double speed;
	double size;

public:
	Ball(double givenSpeed, double givenSize, vector<double> givenMomentum);
	~Ball();

	void MoveBall();
};